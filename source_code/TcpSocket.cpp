#include "TcpSocket.h"

uv_tcp_t* TcpSocket::uv_tcp_socket;
uv_loop_t* TcpSocket::uv_loop;

TcpSocket::TcpSocket(uv_stream_t *handle, int status, uv_loop_t *loop)
  : uv_loop(loop)
{
  if(status < 0)
    {
      fprintf(stderr, "New connection error %s\n", uv_strerror(status));
      return;
    }

  uv_tcp_socket = (uv_tcp_t*) malloc(sizeof(uv_tcp_t));
  uv_tcp_init(uv_loop, uv_tcp_socket);

  if(uv_accept(handle, (uv_stream_t*)uv_tcp_socket) == 0)
    {
      uv_read_start((uv_stream_t*)uv_tcp_socket, allocBuffer, tcpRead);
    }
  else
    {
      uv_close((uv_handle_t*) uv_tcp_socket, NULL);
    }
}

void TcpSocket::tcpRead(uv_stream_t *handle, ssize_t nread, const uv_buf_t *buf)
{
  SocketDescriptor socketDiscriptor = getSocketDescriptor((uv_handle_t *)handle);

  if(nread > 0)
    {
      HiveClientBuffer *hiveClient;
      if(buffer_hash.contains(socketDiscriptor))
        {
          Log::net(Log::Normal, "UvServer::tcpRead()", "Reading message form old user: " + QString::number(socketDiscriptor));
          hiveClient = buffer_hash.value(socketDiscriptor);
        }
      else
        {
          Log::net(Log::Normal, "UvServer::tcpRead()", "Reading message form new user: " + QString::number(socketDiscriptor));
          hiveClient = new HiveClientBuffer();
          buffer_hash.insert(socketDiscriptor, hiveClient);
        }

      uv_buf_t buffer = uv_buf_init(buf->base, nread);
      decodeTcp(QString::fromUtf8(buffer.base, buffer.len), hiveClient);

      // << echo server
      write_req_t *req = (write_req_t*)malloc(sizeof(write_req_t));
      req->buf = uv_buf_init(buf->base, nread);
      uv_write((uv_write_t*)req, handle, &req->buf, 1, tcpWriteCb);

      return;
    }
  if(nread < 0)
    {
      if (nread != UV_EOF)
        {
          fprintf(stderr, "TCP Read error %s\n", uv_err_name(nread));
        }
      Log::net(Log::Normal, "UvServer::tcpRead()", "Disconnected from discriptor: " + QString::number(socketDiscriptor));

      uv_close((uv_handle_t*)handle, NULL); // NULL is a close callback
    }

  free(buf->base);
}

void TcpSocket::tcpWriteCb(uv_write_t *handle, int status)
{
  if (status)
    {
      fprintf(stderr, "Write error %s\n", uv_strerror(status));
    }

  freeWriteReq(handle);
}

void TcpSocket::allocBuffer(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf)
{
  buf->base = (char*) malloc(suggested_size);
  buf->len = suggested_size;
}

void TcpSocket::freeWriteReq(uv_write_t *handle)
{
  write_req_t *wr = (write_req_t*) handle;
  free(wr->buf.base);
  free(wr);
}

int TcpSocket::getSocketDescriptor(uv_handle_t *handle)
{
  int fd;
  uv_fileno(handle, &fd);
  return fd;
}
