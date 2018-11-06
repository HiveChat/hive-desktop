#ifndef HIVEUDPSERVER_H
#define HIVEUDPSERVER_H

#define UDP_PORT 23232

#include "../libs/libParsley/include/PTimer.h"
#include "../libs/libParsley/include/PUdpSocket.h"


#include "HiveProtocol.h"

class HiveUdpServer
  : public Parsley::UdpSocket
{
public:
  HiveUdpServer(const char *ip, const int &port, Parsley::Loop *l);
  ~HiveUdpServer();

  void start();
  void stop();

private:

  void udpReadyRead(std::string &data, std::string &ip);

  void onTimedOut(Parsley::Timer* t);

//  static QHash<int, > buffer;
};

#endif // HIVEUDPSERVER_H
