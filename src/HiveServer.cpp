#include "HiveServer.h"

#include <QThread>

int HiveServer::counter = 0;



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
        Parsley::Buffer *msg = new Parsley::Buffer(dat.data(), dat.count(), loop);
        udp_server->write("255.255.255.255", UDP_PORT, msg);

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

void HiveServer::udpPacketReady(std::string &data, std::string &ip)
{
  NetPacket *packet = new NetPacket(ip, data, BaseProtocol::Udp);
  AppDataManager::pushInboundBuffer(packet);
  qDebug()<<"packet received"<<ip.c_str();
}

void HiveServer::onTimedOut(Parsley::Timer *t)
{
  QByteArray dat = HiveProtocol::encodeHeartBeat();
  Parsley::Buffer *msg = new Parsley::Buffer(dat.data(), dat.count(), loop);
  udp_server->write("255.255.255.255", UDP_PORT, msg);
  Log::net(Log::Info, "UvServer::udpHeartBeatCb()", "heart beat sent");
}


//bool
//HiveServer::processHeartBeat(const UsrProfile &usrProfileStruct)
//{
//  if(usrProfileStruct.key.isEmpty())
//    {
//      return false;
//    }

//  if(usrProfileStruct.key == Global::settings.profile_key_str)
//    {
//      if(Global::g_localHostIP != usrProfileStruct.ip)
//        {
//          Global::g_localHostIP = usrProfileStruct.ip;
//        }
//      Log::net(Log::Info, "HiveServer::processHeartBeat", "got heart beat from myself");
////      emit getInstance()->usrEntered(usrProfileStruct);
//    }
//  else
//    {
//      Log::net(Log::Info, "HiveServer::processHeartBeat", "got heart beat from others");
////      emit getInstance()->usrEntered(usrProfileStruct);
//    }
//}

bool
HiveServer::processUsrLeave(QString *usrKey)
{
  if(*usrKey == Global::settings.profile_uuid_str)
    {
//      emit usrLeft(usrKey); << FIX HERE!!

      qDebug()<<"@HiveServer::udpProcessUsrLeft(): Myself left.";
    }

  qDebug()<<"@HiveServer::udpProcessUsrLeft(): Someone left.";
//  emit usrLeft(usrKey); << FIX HERE!!
}

bool
HiveServer::processErrorDelivery()
{

}

bool
HiveServer::processTextMessage()
{
//  if(messageStruct.sender.isEmpty() || messageStruct.reciever.isEmpty())
//    {
//      return;
//    }

//  if(messageStruct.reciever != GlobalData::settings_struct.profile_key_str)
//    {
//      if(messageStruct.sender != GlobalData::settings_struct.profile_key_str)
//        {
//          //no sniffing man!
//          return;
//        }
//      else
//        {
//          qDebug()<<"@NetworkManager::udpProcessMessage(): Got msg I sent: "<<messageStruct.message;
//          emit messageRecieved(messageStruct, true);
//        }
//    }
//  else
//    {
//      if(messageStruct.sender == GlobalData::settings_struct.profile_key_str)
//        {
//          qDebug()<<"@NetworkManager::udpProcessMessage(): me 2 me...";
//          emit messageRecieved(messageStruct, true);
//        }
//      else
//        {
//          qDebug()<<"@NetworkManager::udpProcessMessage(): Other people sent: "<<messageStruct.message;
//          emit messageRecieved(messageStruct, false);
//        }
//    }
}

bool
HiveServer::processFileInfo()
{

}

bool
HiveServer::processFileContent()
{

}

bool
HiveServer::processFileAccept()
{

}

bool
HiveServer::processFileReject()
{

}














