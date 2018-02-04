#ifndef HIVEUDPSERVER_H
#define HIVEUDPSERVER_H

#define UDP_PORT 23232

#include <../libs/libParsley/src/PUdpSocket.h>

class HiveUdpServer
{
public:
  HiveUdpServer(uv_loop_t* loop);

private:
  Parsley::UdpSocket *udp_socket;

  void udpReadyRead(char *data, char *ip);

//  static QHash<int, > buffer;
};

#endif // HIVEUDPSERVER_H
