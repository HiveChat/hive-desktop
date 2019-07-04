#include "HiveServer.h"

#include <QThread>

HiveServer::HiveServer(QObject *parent)
  : QThread(parent)
{
}

HiveServer::~HiveServer()
{
  this->stop();
  delete udp_server;
}

void HiveServer::stop()
{
  heartbeat_timer->stop();
  loop->close();
  Log::net(Log::Info, "HiveServer::close()", "Successfully closed uv event loop.");
}

void
HiveServer::sendTextMessage(const QJsonObject &msg, const BaseProtocol &protocol)
{
  switch (protocol) {
    case BaseProtocol::Udp:
      {
        QByteArray dat = encodeTextMessage(msg);
        udp_server->write("255.255.255.255", UDP_PORT, dat.data());

        Log::net(Log::Info, "HiveServer::sendTextMessage()", "message sent");
        break;
      }
    case BaseProtocol::Tcp:
      {

        break;
      }
    default:
      {

        break;
      }
    }
}

void
HiveServer::run()
{
  Log::net(Log::Info, "HiveServer::run()", "Thread Started");

  loop = new Agio::Loop();
  udp_server = new HiveUdpServer("0.0.0.0", UDP_PORT, loop);
  Agio::on(&udp_server->onReadyRead, this, &HiveServer::udpPacketReady);
  udp_server->start();

  heartbeat_timer = new Agio::Timer(1000, 1000, loop);
  Agio::on(&heartbeat_timer->onTimedOut, this, &HiveServer::onTimedOut);
  heartbeat_timer->start();


//  tcp_server = new Agio::TcpServer("0.0.0.0", TCP_PORT, TCP_BACKLOG, loop);

  loop->run(UV_RUN_DEFAULT);
}

void HiveServer::udpPacketReady(std::string &data, Agio::IPAddress &ip)
{
  NetPacket *packet = new NetPacket(ip.toIPString(), data, BaseProtocol::Udp);
  AppDataManager::pushInboundBuffer(packet);
}

void HiveServer::onTimedOut(Agio::Timer *)
{
  QByteArray dat = HiveProtocol::encodeHeartBeat();
  udp_server->write("255.255.255.255", UDP_PORT, dat.data());
  Log::net(Log::Info, "UvServer::udpHeartBeatCb()", "heart beat sent");
}

