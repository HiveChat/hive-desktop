#ifndef UDPSOCKET_H
#define UDPSOCKET_H


#include "uv_abstract_sock.h"

class UvUdpSockUtils;
class UvUdpSock;


class UvUdpSockUtils
{
protected:
  static QHash<int, UvUdpSock*> udp_sock_hash;

  static void receiveCb(uv_udp_t* handle, ssize_t nread, const uv_buf_t *buf, const sockaddr *addr, unsigned flags);
  static void writeCb(uv_udp_send_t* req, int status);

};


class UvUdpSock
    : public UvAbstractSock
    , protected UvUdpSockUtils
{
public:
  SockReadyReadCb read_cb;

  UvUdpSock(const char* ipAddr, const int &port, uv_loop_t *loop);

  void write(const char *ipAddr, const int &port, const uv_buf_t *buf);

  uv_udp_t* getSocket() {return udp_socket;}


private:
  uv_udp_t* udp_socket;

};

#endif // UDPSOCKET_H
