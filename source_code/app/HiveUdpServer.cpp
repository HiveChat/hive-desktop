#include "HiveUdpServer.h"

#include <functional>

HiveUdpServer::HiveUdpServer(uv_loop_t *loop)
{
  udp_socket = new Parsley::UdpSocket("255.255,255,255", UDP_PORT, loop);
  AbstractSocket::SockReadyReadCb cb = std::bind(&HiveUdpServer::udpReadyRead
                                                 , this
                                                 , std::placeholders::_1
                                                 , std::placeholders::_2);
  udp_socket->bindCb(cb);

}

void HiveUdpServer::udpReadyRead(char *data, char *ip)
{
  QJsonObject json;
  if(!checkJsonPackage(data, &json))
    {
      // do something;
    }





  qDebug()<<data;
}
