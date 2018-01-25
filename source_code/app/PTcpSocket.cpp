#include "PTcpSocket.h"

PTcpSocket::PTcpSocket(uv_loop_t *loop)
{
  uv_loop = loop;
  tcp_socket = (uv_tcp_t*) malloc(sizeof(uv_tcp_t));
  uv_tcp_init(uv_loop, tcp_socket);
}

uv_tcp_t*
PTcpSocket::getSocket()
{
  return tcp_socket;
}

void
PTcpSocket::start()
{
  uv_read_start((uv_stream_t*) tcp_socket, allocBuffer, read);
}

void
PTcpSocket::close()
{
  uv_close((uv_handle_t*) tcp_socket, NULL);
}

void PTcpSocket::connect(const char *addr, const int &port)
{
//  struct sockaddr_in dest = uv_ip4_addr(addr, port);
//  uv_connect_t *connect = (uv_connect_t*) malloc(sizeof(uv_connect_t));
//  uv_tcp_connect(connect, tcp_socket, dest, on_connect);
}

void
PTcpSocket::read(uv_stream_t *handle, ssize_t nread, const uv_buf_t *buf)
{
  SocketDescriptor socketDiscriptor = getSocketDescriptor((uv_handle_t*) handle);

  if(nread > 0)
    {
      uv_buf_t buffer = uv_buf_init(buf->base, nread);
//      decodeTcp(QString::fromUtf8(buffer.base, buffer.len), hiveClient);

      return;
    }
  if(nread < 0)
    {
      if (nread != UV_EOF)
        {
          Log::net(Log::Critical, "TcpSocket::tcpRead()", "TCP Read error: " + QString(uv_err_name(nread)));
        }
      Log::net(Log::Normal, "TcpSocket::tcpRead()", "Disconnected from discriptor: " + QString::number(socketDiscriptor));
      uv_close((uv_handle_t*) handle, NULL);
    }

  free(buf->base);
}

void
PTcpSocket::write(const uv_buf_t *data)
{
  write_req_t *req = (write_req_t*) malloc(sizeof(write_req_t));
  req->buf = uv_buf_init(data->base, data->len);
  uv_write((uv_write_t*) req
           , (uv_stream_t*)tcp_socket
           , &req->buf
           , 1
           , writeCb);
}

void PTcpSocket::setKeepAlive(const bool &enabled, const int &delay)
{
  uv_tcp_keepalive(tcp_socket
                   , enabled ? 1 : 0
                   , delay);
}

void
PTcpSocket::writeCb(uv_write_t *handle, int status)
{
  if(status)
    {
      fprintf(stderr, "Write error %s\n", uv_strerror(status));
    }

  freeWriteReq(handle);
}

void
PTcpSocket::freeWriteReq(uv_write_t *handle)
{
  write_req_t *req = (write_req_t*) handle;
  free(req->buf.base);
  free(req);
}

