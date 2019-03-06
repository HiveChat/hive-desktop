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

  loop = new Parsley::Loop();
  udp_server = new HiveUdpServer("0.0.0.0", UDP_PORT, loop);
  Parsley::connect(&udp_server->onReadyRead, this, &HiveServer::udpPacketReady);
  udp_server->start();

  heartbeat_timer = new Parsley::Timer(1000, 1000, loop);
  Parsley::connect(&heartbeat_timer->onTimedOut, this, &HiveServer::onTimedOut);
  heartbeat_timer->start();


//  tcp_server = new Parsley::TcpServer("0.0.0.0", TCP_PORT, TCP_BACKLOG, loop);

  loop->run(UV_RUN_DEFAULT);
}

void HiveServer::udpPacketReady(std::string &data, Parsley::IPAddress &ip)
{
  NetPacket *packet = new NetPacket(ip.toIPString(), data, BaseProtocol::Udp);
  AppDataManager::pushInboundBuffer(packet);
}

void HiveServer::onTimedOut(Parsley::Timer *)
{
  QByteArray dat = HiveProtocol::encodeHeartBeat();
  udp_server->write("255.255.255.255", UDP_PORT, dat.data());
  Log::net(Log::Info, "UvServer::udpHeartBeatCb()", "heart beat sent");
}

//bool
//HiveServer::processUsrLeave(QString *usrKey)
//{
//  if(*usrKey == Global::settings.profile_uuid_str)
//    {
////      emit usrLeft(usrKey); << FIX HERE!!

//      qDebug()<<"@HiveServer::udpProcessUsrLeft(): Myself left.";
//    }

//  qDebug()<<"@HiveServer::udpProcessUsrLeft(): Someone left.";
////  emit usrLeft(usrKey); << FIX HERE!!
//}
