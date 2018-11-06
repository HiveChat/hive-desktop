#include "HiveUdpServer.h"


HiveUdpServer::HiveUdpServer(const char *ip, const int &port, Parsley::Loop *l)
  : Parsley::UdpSocket(ip, port, l)
{
  Parsley::connect(&this->onReadyRead, this, &HiveUdpServer::udpReadyRead);
}

HiveUdpServer::~HiveUdpServer()
{
  qDebug()<<"stopping timer";
}

void HiveUdpServer::start()
{

  Parsley::UdpSocket::start();
}

void HiveUdpServer::stop()
{
  Parsley::UdpSocket::stop();
}

/*!
 * \brief HiveUdpServer::udpReadyRead
 * \param data Received data in the callback from Parsley::UdpSocket.
 * \param ip IP address in the callback from Parsley::UdpSocket.
 * \note Any Json decoding should not appear in network thread, because it will be a bottle neck of net speed. Will be removed after several testings.
 */
void HiveUdpServer::udpReadyRead(std::string &data, std::string &ip)
{
  Log::net(Log::Info, "HiveUdpServer::udpReadyRead()", "Packet!!!!!!!!!!!!");

  onReadyRead.call(data, ip);
}

