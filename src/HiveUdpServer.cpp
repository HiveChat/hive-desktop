#include "HiveUdpServer.h"


HiveUdpServer::HiveUdpServer(const char *ip, const int &port, Parsley::Loop *l)
  : Parsley::UdpSocket(ip, port, l)
{
}

HiveUdpServer::~HiveUdpServer()
{
}

void HiveUdpServer::start()
{
  Parsley::UdpSocket::start();
}

void HiveUdpServer::stop()
{
  Parsley::UdpSocket::stop();
}


