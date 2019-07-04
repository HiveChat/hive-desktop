#include "HiveUdpServer.h"


HiveUdpServer::HiveUdpServer(const char *ip, const int &port, Agio::Loop *l)
  : Agio::UdpSocket(ip, port, l)
{
}

HiveUdpServer::~HiveUdpServer()
{
}

int HiveUdpServer::start()
{
  Agio::UdpSocket::start();
}

void HiveUdpServer::stop()
{
  Agio::UdpSocket::stop();
}


