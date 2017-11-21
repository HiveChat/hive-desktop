#ifndef UDPSOCKET_H
#define UDPSOCKET_H

#include "Log.h"

#include <uv.h>

class UdpSocket
{
public:
  UdpSocket(const char* ipAddr, const int &port, const bool keepAlive, uv_loop_t *loop);

  void write(const char *ipAddr, const int &port, const uv_buf_t *buf);

  uv_udp_t* getSocket() {return udp_socket;}

private:
  static bool keep_alive;
  static uv_udp_t* udp_socket;
  static uv_loop_t* uv_loop;

  static void read(uv_udp_t *handle, ssize_t nread, const uv_buf_t *buf, const sockaddr *addr, unsigned flags);
  static void writeCb(uv_udp_send_t* req, int status);
  static void allocBuffer(uv_handle_t *handle, size_t suggestedSize, uv_buf_t *buf);

};

#endif // UDPSOCKET_H
