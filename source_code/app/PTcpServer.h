#ifndef TCPSERVER_H
#define TCPSERVER_H

#define TCP_PORT 23232
#define TCP_BACKLOG 128

#include "PTcpSocket.h"

class PTcpServer
{
public:
  PTcpServer(const char* ipAddr, const int &port, const int &backLog, uv_loop_t *loop);

private:
  static uv_tcp_t* uv_tcp_server;
  static uv_loop_t* uv_loop;

  static bool accept(uv_stream_t *handle, PTcpSocket *client);
  static void tcpNewConnectionCb(uv_stream_t *handle, int status);
  static void allocBuffer(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf);
};

#endif // TCPSERVER_H
