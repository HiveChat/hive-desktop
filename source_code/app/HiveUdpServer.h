#ifndef HIVEUDPSERVER_H
#define HIVEUDPSERVER_H

#define UDP_PORT 23233

#include "../libs/libParsley/src/PTimer.h"


#include "HiveAbstractServer.h"
#include "HiveProtocol.h"

class HiveUdpServer
    : public HiveAbstractServer
    , public HiveProtocol
{
public:
  HiveUdpServer(Parsley::Loop *loop);
  ~HiveUdpServer();

  bool start();
  bool stop();
//  void bindCb(const Parsley::AbstractSocket::SockReadyReadCb &cb);

private:
  Parsley::UdpSocket *udp_socket;
  Parsley::Timer *heartbeat_timer; // Move this to another thread in the future, this heartbeat is on application level

  void udpReadyRead(const Parsley::Buffer &data, char *ip);

//  static QHash<int, > buffer;
};

#endif // HIVEUDPSERVER_H
