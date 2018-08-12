#include "HiveServer.h"

#include <QThread>

int HiveServer::counter = 0;



HiveServer::HiveServer(QObject *parent)
  : QThread(parent)
{
}

HiveServer::~HiveServer()
{
  delete udp_server;
}

void HiveServer::stop()
{
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
        uv_buf_t msg = uv_buf_init(dat.data(), dat.count());
//        udp_server->write("255.255.255.255", 23232, &msg);

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
  qDebug()<<"uv thread id: "<<this->currentThreadId();
  Log::net(Log::Info, "HiveServer::run()", "Thread Started");

  loop = new Parsley::Loop();
  udp_server = new HiveUdpServer(loop);
  udp_server->bindCb(std::bind(&HiveServer::udpPacketReady
                               , this
                               , std::placeholders::_1
                               , std::placeholders::_2));
  udp_server->start();
//  tcp_server = new Parsley::TcpServer("0.0.0.0", TCP_PORT, TCP_BACKLOG, loop);
  loop->run(UV_RUN_DEFAULT);

  Log::net(Log::Info, "HiveServer::run()", "Quit Thread");
}

void HiveServer::udpPacketReady(const Parsley::Buffer &data, char *ip)
{
  NetPacket *packet = new NetPacket(ip, data.base, data.len, BaseProtocol::Udp);
  AppDataManager::pushInboundBuffer(packet);
  qDebug()<<"packet received"<<ip;
}


bool
HiveServer::processHeartBeat(const UsrProfile &usrProfileStruct)
{
  if(usrProfileStruct.key.isEmpty())
    {
      return false;
    }

  if(usrProfileStruct.key == Global::settings.profile_key_str)
    {
      if(Global::g_localHostIP != usrProfileStruct.ip)
        {
          Global::g_localHostIP = usrProfileStruct.ip;
        }
      Log::net(Log::Info, "HiveServer::processHeartBeat", "got heart beat from myself");
//      emit getInstance()->usrEntered(usrProfileStruct);
    }
  else
    {
      Log::net(Log::Info, "HiveServer::processHeartBeat", "got heart beat from others");
//      emit getInstance()->usrEntered(usrProfileStruct);
    }
}

bool
HiveServer::processUsrLeave(QString *usrKey)
{
  if(*usrKey == Global::settings.profile_key_str)
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














