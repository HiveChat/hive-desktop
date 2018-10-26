#ifndef HIVEUDPSERVER_H
#define HIVEUDPSERVER_H

#define UDP_PORT 23232

#include "../libs/libParsley/include/PTimer.h"
#include "../libs/libParsley/include/PUdpSocket.h"


#include "HiveProtocol.h"

class HiveUdpServer
//  : public Parsley::UdpSocket
{
public:
  HiveUdpServer(Parsley::Loop *loop);
  ~HiveUdpServer();

  bool start();
  bool stop();

  Parsley::Callback<void, Parsley::Buffer*, char*> onReadyRead;

private:
  Parsley::UdpSocket *udp_socket;
  Parsley::Timer *heartbeat_timer;

  void udpReadyRead(Parsley::Buffer *data, char *ip);

  void onTimedOut(Parsley::Timer* t);

//  static QHash<int, > buffer;
};

#endif // HIVEUDPSERVER_H
