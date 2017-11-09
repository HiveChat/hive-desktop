#include "TcpServer.h"

uv_tcp_t* TcpServer::uv_tcp_server;
uv_loop_t* TcpServer::uv_loop;


TcpServer::TcpServer(uv_loop_t *loop)
{
  uv_loop = loop;
  struct sockaddr_in *tcpAddr = (sockaddr_in*)malloc(sizeof(sockaddr_in));
  uv_ip4_addr("0.0.0.0", TCP_PORT, tcpAddr);
  uv_tcp_server = (uv_tcp_t*) malloc(sizeof(uv_tcp_t));
  uv_tcp_init(uv_loop, uv_tcp_server);
  uv_tcp_bind(uv_tcp_server, (const struct sockaddr*) tcpAddr, 0);
  int r = uv_listen((uv_stream_t*) uv_tcp_server, TCP_BACKLOG, tcpNewConnectionCb);
  if(r)
    {
      Log::net(Log::Error, "UvServer::run()", QString("Listen error: " + QString(uv_strerror(r))));
      fprintf(stderr, "Listen error %s\n", uv_strerror(r));
    }


}

void TcpServer::tcpNewConnectionCb(uv_stream_t *handle, int status)
{
  if(status < 0)
    {
      fprintf(stderr, "New connection error %s\n", uv_strerror(status));
      return;
    }

  uv_tcp_t *client = (uv_tcp_t*)malloc(sizeof(uv_tcp_t));
  uv_tcp_init(uv_loop, client);


  if(uv_accept(handle, (uv_stream_t*)client) == 0)
    {
      uv_read_start((uv_stream_t*)client, allocBuffer, tcpReadCb);
    }
  else
    {
      uv_close((uv_handle_t*) client, NULL);
    }
}

void TcpServer::allocBuffer(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf)
{
  buf->base = (char*) malloc(suggested_size);
  buf->len = suggested_size;
}
