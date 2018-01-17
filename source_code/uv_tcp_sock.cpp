#include "uv_tcp_sock.h"

uv_tcp_t* UvTcpSock::tcp_socket;
uv_loop_t* UvTcpSock::uv_loop;

UvTcpSock::UvTcpSock(uv_loop_t *loop)
{
  uv_loop = loop;
  tcp_socket = (uv_tcp_t*) malloc(sizeof(uv_tcp_t));
  uv_tcp_init(uv_loop, tcp_socket);
}

uv_tcp_t*
UvTcpSock::getSocket()
{
  return tcp_socket;
}

void
UvTcpSock::start()
{
  uv_read_start((uv_stream_t*) tcp_socket, allocBuffer, read);
}

void
UvTcpSock::close()
{
  uv_close((uv_handle_t*) tcp_socket, NULL);
}

void UvTcpSock::connect(const char *addr, const int &port)
{
//  struct sockaddr_in dest = uv_ip4_addr(addr, port);
//  uv_connect_t *connect = (uv_connect_t*) malloc(sizeof(uv_connect_t));
//  uv_tcp_connect(connect, tcp_socket, dest, on_connect);
}

void
UvTcpSock::read(uv_stream_t *handle, ssize_t nread, const uv_buf_t *buf)
{
  SocketDescriptor socketDiscriptor = getSocketDescriptor();

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
UvTcpSock::write(const uv_buf_t *data)
{
  write_req_t *req = (write_req_t*) malloc(sizeof(write_req_t));
  req->buf = uv_buf_init(data->base, data->len);
  uv_write((uv_write_t*) req
           , (uv_stream_t*)tcp_socket
           , &req->buf
           , 1
           , writeCb);
}

void UvTcpSock::setKeepAlive(const bool &enabled, const int &delay)
{
  uv_tcp_keepalive(tcp_socket
                   , enabled ? 1 : 0
                   , delay);
}

void
UvTcpSock::writeCb(uv_write_t *handle, int status)
{
  if (status)
    {
      fprintf(stderr, "Write error %s\n", uv_strerror(status));
    }

  freeWriteReq(handle);
}

void
UvTcpSock::allocBuffer(uv_handle_t *handle, size_t suggestedSize, uv_buf_t *buf)
{
  buf->base = (char*) malloc(suggestedSize);
  buf->len = suggestedSize;
}

void
UvTcpSock::freeWriteReq(uv_write_t *handle)
{
  write_req_t *req = (write_req_t*) handle;
  free(req->buf.base);
  free(req);
}

int
UvTcpSock::getSocketDescriptor()
{
  int fd;
#ifdef Q_OS_WIN
  uv_fileno((uv_handle_t*) tcp_socket, (uv_os_fd_t*)(&fd));
#else
  uv_fileno((uv_handle_t*) tcp_socket, &fd);
#endif
  return fd;
}
