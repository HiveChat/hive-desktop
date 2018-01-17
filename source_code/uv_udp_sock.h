#ifndef UDPSOCKET_H
#define UDPSOCKET_H


#include "uv_abstract_sock.h"

class UvUdpSockUtils;
class UvUdpSock;


class UvUdpSockUtils
{
protected:
  static void read(uv_udp_t *handle, ssize_t nread, const uv_buf_t *buf, const sockaddr *addr, unsigned flags);
  static void onWritten(uv_udp_send_t* req, int status);
};


class UvUdpSock
    : protected UvAbstractSock
    , protected UvUdpSockUtils
{
public:
  UvUdpSock(const char* ipAddr, const int &port, uv_loop_t *loop);

  void write(const char *ipAddr, const int &port, const uv_buf_t *buf);

  uv_udp_t* getSocket() {return udp_socket;}

private:
  uv_udp_t* udp_socket;
  uv_loop_t* uv_loop;

};

#endif // UDPSOCKET_H
