#ifndef HIVEUDPSERVER_H
#define HIVEUDPSERVER_H

#define UDP_PORT 23232

#include <libagio/timer.h>
#include <libagio/udp_socket.h>


#include "HiveProtocol.h"

class HiveUdpServer
  : public Agio::UdpSocket
{
public:
  HiveUdpServer(const char *ip, const int &port, Agio::Loop *l);
  ~HiveUdpServer();

  int start();
  void stop();

private:
  void onTimedOut(Agio::Timer* t);

};

#endif // HIVEUDPSERVER_H
