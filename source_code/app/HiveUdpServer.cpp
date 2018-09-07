#include "HiveUdpServer.h"


HiveUdpServer::HiveUdpServer(Parsley::Loop *loop)
{
  udp_socket = new Parsley::UdpSocket("255.255,255,255", UDP_PORT, loop);
  Parsley::connect(&udp_socket->onReadyRead, this, &HiveUdpServer::udpReadyRead);
  heartbeat_timer = new Parsley::Timer(1000, 1000, loop);
  Parsley::connect(&heartbeat_timer->onTimedOut, this, &HiveUdpServer::onTimedOut);
}

HiveUdpServer::~HiveUdpServer()
{
  heartbeat_timer->stop();
  qDebug()<<"stopping timer";
}

bool HiveUdpServer::start()
{
  udp_socket->start();
  heartbeat_timer->start();
}

bool HiveUdpServer::stop()
{
  heartbeat_timer->stop();
  udp_socket->stop();
}

/*!
 * \brief HiveUdpServer::udpReadyRead
 * \param data Received data in the callback from Parsley::UdpSocket.
 * \param ip IP address in the callback from Parsley::UdpSocket.
 * \note Any Json decoding should not appear in network thread, because it will be a bottle neck of net speed. Will be removed after several testings.
 */
void HiveUdpServer::udpReadyRead(Parsley::Buffer data, char *ip)
{
  onReadyRead.call(data, ip);
}

void HiveUdpServer::onTimedOut(Parsley::Timer *t)
{
  QByteArray dat = encodeHeartBeat();
  Parsley::Buffer msg = uv_buf_init(dat.data(), dat.count());
  udp_socket->write("255.255.255.255", UDP_PORT, &msg);
  Log::net(Log::Info, "UvServer::udpHeartBeatCb()", "heart beat sent");
}
