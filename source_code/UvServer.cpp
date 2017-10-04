#include "UvServer.h"


uv_loop_t* UvServer::loop;
QHash<UvServer::SocketDescriptor, HiveProtocol::HiveClient*> UvServer::buffer_hash;
QHash<QString, UvServer::SocketDescriptor> UvServer::key_sd_hash;


UvServer::UvServer(QObject *parent) : QThread(parent)
{
}

UvServer::~UvServer()
{

}

void
UvServer::run()
{
  qDebug()<<"uv thread id: "<<this->currentThreadId();
  Log::net(Log::Normal, "UvServer::run()", "Thread Started");

  loop = uv_default_loop();

  struct sockaddr_in udpAddr;
  uv_ip4_addr("0.0.0.0", UDP_PORT, &udpAddr);
  uv_udp_t udpServer;
  uv_udp_init(loop, &udpServer);
  uv_udp_bind(&udpServer, (const struct sockaddr *)&udpAddr, UV_UDP_REUSEADDR);
  uv_udp_recv_start(&udpServer, allocBuffer, udpRead);


  //< udp test
  uv_buf_t buffer;
  allocBuffer(NULL, 256, &buffer);
  memset(buffer.base, 8, buffer.len);

  uv_udp_send_t send_req;
  uv_buf_t discover_msg = buffer;

  struct sockaddr_in send_addr;
  uv_ip4_addr("127.0.0.1", 23232, &send_addr);
  uv_udp_send(&send_req, &udpServer, &discover_msg, 1, (const struct sockaddr *)&send_addr, NULL);




  struct sockaddr_in tcpAddr;
  uv_ip4_addr("0.0.0.0", TCP_PORT, &tcpAddr);
  uv_tcp_t tcp_server;
  uv_tcp_init(loop, &tcp_server);
  uv_tcp_bind(&tcp_server, (const struct sockaddr*)&tcpAddr, 0);
  int r = uv_listen((uv_stream_t*)&tcp_server, TCP_BACKLOG, tcpNewConnection);
  if(r)
    {
      Log::net(Log::Error, "UvServer::run()", QString("Listen error: " + QString(uv_strerror(r))));
      fprintf(stderr, "Listen error %s\n", uv_strerror(r));
    }
  uv_run(loop, UV_RUN_DEFAULT);
  Log::net(Log::Normal, "UvServer::run()", "Quit Thread");

}

void UvServer::quit()
{
  uv_stop(loop);
  Log::net(Log::Normal, "UvServer::closeUvLoop()", "Successfully closed uv event loop.");

  QThread::quit();
}

void
UvServer::udpRead(uv_udp_t *req, ssize_t nread, const uv_buf_t *buffer, const struct sockaddr *addr, unsigned flags)
{
  if(nread >= 0 && addr) //addr sometimes is a nullptr
    {
      char sender[17] = { 0 };
      uv_ip4_name((const struct sockaddr_in*)addr, sender, 16);
      fprintf(stderr, "Recv from %s\n", sender);
      qDebug()<<"base:"<<buffer->base;
      qDebug()<<decodeHivePacket(QString::fromStdString(buffer->base));
    }
  else
    {
      fprintf(stderr, "UDP Read error %s\n", uv_err_name(nread));
//      uv_close((uv_handle_t*) req, NULL);
    }

  free(buffer->base);
  return;
}

void UvServer::udpWrite()
{

}

void
UvServer::tcpNewConnection(uv_stream_t *server, int status)
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
UvServer::tcpRead(uv_stream_t *client, ssize_t nread, const uv_buf_t *buf)
{
  if(nread > 0)
    {
      SocketDescriptor socketDiscriptor = getSocketDescriptor(client);
      HiveClient *hiveClient;
      if(buffer_hash.contains(socketDiscriptor))
        {
          Log::net(Log::Normal, "UvServer::tcpRead()", "Reading message form old user: " + QString::number(socketDiscriptor));
          hiveClient = buffer_hash.value(socketDiscriptor);
        }
      else
        {
          Log::net(Log::Normal, "UvServer::tcpRead()", "Reading message form new user: " + QString::number(socketDiscriptor));
          hiveClient = new HiveClient();
          buffer_hash.insert(socketDiscriptor, hiveClient);
        }

      uv_buf_t buffer = uv_buf_init(buf->base, nread);
      readTcp(QString::fromUtf8(buffer.base, buffer.len), hiveClient);

      // << echo server
      write_req_t *req = (write_req_t*)malloc(sizeof(write_req_t));
      req->buf = uv_buf_init(buf->base, nread);
      uv_write((uv_write_t*)req, client, &req->buf, 1, tcpWriten);

      return;
    }
  if(nread < 0) {
      if (nread != UV_EOF)
        {
          fprintf(stderr, "TCP Read error %s\n", uv_err_name(nread));
        }
      int socketDiscriptor = getSocketDescriptor(client);
      Log::net(Log::Normal, "UvServer::tcpRead()", "Disconnected from discriptor: " + QString::number(socketDiscriptor));

      uv_close((uv_handle_t*)client, NULL); // NULL is a close callback
    }

  free(buf->base);
}

void
UvServer::tcpWriten(uv_write_t *req, int status)
{
  if (status)
    {
      fprintf(stderr, "Write error %s\n", uv_strerror(status));
    }
  freeWriteReq(req);
}

void
UvServer::allocBuffer(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf)
{
  buf->base = (char*) malloc(suggested_size);
  buf->len = suggested_size;
}

void
UvServer::freeWriteReq(uv_write_t *req)
{
  write_req_t *wr = (write_req_t*) req;
  free(wr->buf.base);
  free(wr);
}

int
UvServer::getSocketDescriptor(uv_stream_t *handle)
{
  int fd;
  uv_fileno((uv_handle_t *)handle, &fd);
  return fd;
}







