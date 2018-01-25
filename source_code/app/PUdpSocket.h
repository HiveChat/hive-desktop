#ifndef UDPSOCKET_H
#define UDPSOCKET_H


#include "PAbstractSocket.h"

class PUdpSocketUtils;
class PUdpSocket;


class PUdpSocketUtils
{
protected:
  static QHash<int, PUdpSocket*> instance_hash;
  static bool registerInstance(PUdpSocket *sock);

  static void receiveCb(uv_udp_t* handle, ssize_t nread, const uv_buf_t *buf, const sockaddr *addr, unsigned flags);
  static void writeCb(uv_udp_send_t* req, int status);

};


class PUdpSocket
    : public PAbstractSocket
    , protected PUdpSocketUtils
{
public:
  SockReadyReadCb read_cb;

  PUdpSocket(uv_loop_t *loop);
  PUdpSocket(const char *ipAddr, const int &port, uv_loop_t *loop);

  void bind(const char *ipAddr, const int &port);
  void start();
  void stop();
  void write(const char *ipAddr, const int &port, const uv_buf_t *buf);
  void setBroadcatEnabled(const bool &enabled = true);

  uv_udp_t* getSocket() {return udp_socket;}


protected:
  uv_udp_t* udp_socket;

};

#endif // UDPSOCKET_H
