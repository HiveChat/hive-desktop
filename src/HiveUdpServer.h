#ifndef HIVEUDPSERVER_H
#define HIVEUDPSERVER_H

#define UDP_PORT 23232

#include "libparsley/timer.h"
#include "libparsley/udp_socket.h"


#include "HiveProtocol.h"

class HiveUdpServer
  : public Parsley::UdpSocket
{
public:
  HiveUdpServer(const char *ip, const int &port, Parsley::Loop *l);
  ~HiveUdpServer();

  int start();
  void stop();

private:
  void onTimedOut(Parsley::Timer* t);

};

#endif // HIVEUDPSERVER_H
