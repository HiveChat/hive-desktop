#include "HiveUdpServer.h"


HiveUdpServer::HiveUdpServer(uv_loop_t *loop)
{
  udp_socket = new Parsley::UdpSocket("255.255,255,255", UDP_PORT, loop);
  udp_socket->bindCb(std::bind(&HiveUdpServer::udpReadyRead
                               , this
                               , std::placeholders::_1
                               , std::placeholders::_2));

  heartbeat_timer = new Parsley::Timer(1000, 1, loop);
  heartbeat_timer->bindCb([this](Parsley::Timer*){
    QByteArray dat = encodeHeartBeat();
    uv_buf_t msg = uv_buf_init(dat.data(), dat.count());
    udp_socket->write("255.255.255.255", UDP_PORT, &msg);
    Log::net(Log::Normal, "UvServer::udpHeartBeatCb()", "heart beat sent");
  });
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

void HiveUdpServer::udpReadyRead(char *data, char *ip)
{
  QJsonParseError err;
  QJsonDocument doc = QJsonDocument::fromJson(data, &err);
  if(err.error != QJsonParseError::NoError
     || !doc.isObject())
    {
      Log::net(Log::Critical
               , "HiveAbstractServer::checkJsonPackage()"
               , QString(err.errorString() + " in stream: " + data));

      //! TODO: Error Handling
      return;
    }

  QJsonObject obj = doc.object();
  QString rUuid = obj.value("receiver").toString();
  if(rUuid != Global::settings.profile_key_str
     && rUuid != "{00000000-0000-0000-0000-000000000000}")
    {
      Log::net(Log::Error
               , "HiveAbstractServer::checkJsonPackage()"
               , "Package belongs to " + obj.value("receiver").toString());

      //! TODO: Error Handling
      return;
    }

//  for(int i = 0; i < 1000; i ++)
//    {
//      for(int j = 0; j < 100; j ++)
//        {
//          for(int k = 0; k < 10; k ++)
//            {
//              i ++;
//              i --;
//            }
//        }
//    }

  callPacketReady(obj);
}
