#include "UvTcpServer.h"

uv_loop_t* UvTcpServer::loop;
struct sockaddr_in UvTcpServer::addr;
QHash<UvTcpServer::SocketDescriptor, Bee*> UvTcpServer::bee_hash;
QHash<QString, UvTcpServer::SocketDescriptor> UvTcpServer::key_sd_hash;


UvTcpServer::UvTcpServer(QObject *parent) : QThread(parent)
{
}

UvTcpServer::~UvTcpServer()
{
}

void
UvTcpServer::closeUvLoop()
{
  uv_stop(loop);
  Log::net(Log::Normal, "UvTcpServer::closeUvLoop()", "Successfully closed uv event loop.");
}

void
UvTcpServer::run()
{
  qDebug()<<"uv thread id: "<<this->currentThreadId();
  Log::net(Log::Normal, "UvTcpServer::run()", "Thread Started");

  loop = uv_default_loop();

  uv_tcp_t server;
  uv_tcp_init(loop, &server);

  uv_ip4_addr("0.0.0.0", TCP_PORT, &addr);
  uv_tcp_bind(&server, (const struct sockaddr*)&addr, 0);

  int r = uv_listen((uv_stream_t*)&server, TCP_BACKLOG, onNewConnection);
  if(r)
    {
      Log::net(Log::Error, "UvTcpServer::run()", QString("Listen error: " + QString(uv_strerror(r))));
      fprintf(stderr, "Listen error %s\n", uv_strerror(r));
    }
  uv_run(loop, UV_RUN_DEFAULT);

  Log::net(Log::Normal, "UvTcpServer::run()", "Quit Thread");

}

void
UvTcpServer::onNewConnection(uv_stream_t *server, int status)
{
  if(status < 0)
    {
      fprintf(stderr, "New connection error %s\n", uv_strerror(status));
      return;
    }

  uv_tcp_t *client = (uv_tcp_t*)malloc(sizeof(uv_tcp_t));
  uv_tcp_init(loop, client);


  if(uv_accept(server, (uv_stream_t*)client) == 0)
    {
      uv_read_start((uv_stream_t*)client, allocBuffer, tcpRead);
    }
  else
    {
      uv_close((uv_handle_t*) client, NULL);
    }
}

void
UvTcpServer::tcpRead(uv_stream_t *client, ssize_t nread, const uv_buf_t *buf)
{
  if (nread > 0)
    {
      SocketDescriptor socketDiscriptor = getSocketDescriptor(client);
      Bee *bee;
      if(bee_hash.contains(socketDiscriptor))
        {
          Log::net(Log::Normal, "UvTcpServer::tcpRead()", "Reading message form old user: " + QString::number(socketDiscriptor));
          bee = bee_hash.value(socketDiscriptor);
        }
      else
        {
          Log::net(Log::Normal, "UvTcpServer::tcpRead()", "Reading message form new user: " + QString::number(socketDiscriptor));
//          bee = new Bee(client, socketDiscriptor);
          bee_hash.insert(socketDiscriptor, bee);
        }

      uv_buf_t buffer = uv_buf_init(buf->base, nread);
      bee->read(QString::fromUtf8(buffer.base, buffer.len));

      write_req_t *req = (write_req_t*)malloc(sizeof(write_req_t));
      req->buf = uv_buf_init(buf->base, nread);

      uv_write((uv_write_t*)req, client, &req->buf, 1, tcpWrite);

      return;
    }
  if (nread < 0) {
      if (nread != UV_EOF)
        {
          fprintf(stderr, "Read error %s\n", uv_err_name(nread));
        }
      int socketDiscriptor = getSocketDescriptor(client);
      Log::net(Log::Normal, "UvTcpServer::tcpRead()", "Disconnected from discriptor: " + QString::number(socketDiscriptor));

      uv_close((uv_handle_t*)client, NULL); // NULL is a close callback
    }

  free(buf->base);
}

void
UvTcpServer::tcpWrite(uv_write_t *req, int status)
{
  if (status)
    {
      fprintf(stderr, "Write error %s\n", uv_strerror(status));
    }
  freeWriteReq(req);
}

void
UvTcpServer::allocBuffer(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf)
{
  buf->base = (char*) malloc(suggested_size);
  buf->len = suggested_size;
}

void
UvTcpServer::freeWriteReq(uv_write_t *req)
{
  write_req_t *wr = (write_req_t*) req;
  free(wr->buf.base);
  free(wr);
}

int
UvTcpServer::getSocketDescriptor(uv_stream_t *handle)
{
  int fd;
  uv_fileno((uv_handle_t *)handle, (void**)&fd);
  return fd;
}





//Bee::Bee(uv_stream_t *tcpHandle, const int &fd)
//  : tcp_handle(tcpHandle)
//  , socket_descriptor(fd)
//{
//}

bool Bee::read(const QString &data) //recursion decode
{
  Log::net(Log::Normal, "Bee::read()", "Stream: " + data);

  buffer.append(data);

  //if size header is 0
  if(read_size == 0)
    {
      //if 16 digit size header is not complete, return
      if(buffer.size() < 16)
        {
          Log::net(Log::Normal, "Bee::read()", "Failed: value \"size\" in header is not complete");
          return false;
        }
      else
        {
          read_size = buffer.mid(0, 16).toInt();
          buffer.remove(0, 16);
          Log::net(Log::Normal, "Bee::read()", "Member read_size is set to " + QString::number(read_size));
        }
    }

  //if data is not complete, return
  if(buffer.size() < read_size)
    {
      Log::net(Log::Normal, "Bee::read()", "Failed: buffer not filled.");
      return false;
    }
  else //else read
    {
      QString packet = buffer.mid(0, read_size);
      buffer.remove(0, read_size);
      read_size = 0;

      Log::net(Log::Normal, "Bee::read()", "Get packet: " + packet);

      if(!decodePacket(packet))
        {
          Log::net(Log::Error, "bool Bee::readBuffer()", "Packet decode failed!");
          buffer.clear();

          return false;
        }
    }


  return read("");
}

bool Bee::write(const MessageType &MsgType, const QString &data)
{

}

bool Bee::isLeaving()
{
  return is_leaving;
}

bool Bee::isIdentified()
{
  return usr_data == nullptr;
}

bool Bee::decodePacket(const QString &data)
{
  QByteArray byteArray = data.toLatin1();
  QJsonParseError jsonError;
  QJsonDocument readJsonDocument = QJsonDocument::fromJson(byteArray, &jsonError);
  if(jsonError.error != QJsonParseError::NoError && !readJsonDocument.isObject())
    {
      Log::net(Log::Critical, "Bee::decodePacket()", jsonError.errorString());
      Log::net(Log::Critical, "Bee::decodePacket()", "Stream: " + data);
      return false;
    }

  QJsonObject packetJson;
  QString receiverKey = packetJson.value("receiver").toString();
  if(receiverKey != GlobalData::settings_struct.profile_key_str)
    {
      Log::net(Log::Error, "Bee::decodePacket()", "Package delivered to wrong person!");
      return false;
    }
  MessageType messageType = (MessageType)packetJson.value("type").toInt();
  switch (messageType) {
    case MessageType::FileContent:
      {

        break;
      }
    case MessageType::FileInfo:
      {

        break;
      }
    case MessageType::FileReject:
      {

        break;
      }
    case MessageType::FileAccept:
      {

        break;
      }
    case MessageType::ErrorDelivery:
      {

        break;
      }
  }
}
