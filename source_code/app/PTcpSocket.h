#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#include "PAbstractSocket.h"
#include <functional>
#include <stdlib.h>

class PTcpSocketUtils;
class PTcpSocket;

class PTcpSocketUtils
{
public:

//protected:

};

class PTcpSocket
    : protected PAbstractSocket
    , protected PTcpSocketUtils
{
  typedef struct {
    uv_write_t req;
    uv_buf_t buf;
  } write_req_t;


public:
  PTcpSocket(uv_loop_t *loop);

  void start();
  void close();
  void connect(const char* addr, const int &port);
  void write(const uv_buf_t *data);

  void setKeepAlive(const bool &enabled, const int &delay);

  uv_tcp_t* getSocket();

  SockReadyReadCb read_cb;


protected:
  uv_tcp_t* tcp_socket;

  static void read(uv_stream_t *handle, ssize_t nread, const uv_buf_t *buf);
  static void writeCb(uv_write_t *handle, int status);
  static void freeWriteReq(uv_write_t *handle);
};

#endif // TCPSOCKET_H
