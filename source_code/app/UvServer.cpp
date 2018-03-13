#include "UvServer.h"

#include <QThread>

Parsley::Loop* UvServer::loop;
Parsley::TcpServer* UvServer::tcp_server;
int UvServer::counter = 0;



UvServer::UvServer(QObject *parent)
  : QThread(parent)
{
}

UvServer::~UvServer()
{
  delete udp_server;
}

void
UvServer::quit()
{
  int result = loop->close();
  if (result == UV_EBUSY)
    {
      uv_walk_cb uvWalkCb = [](uv_handle_t* handle, void* arg) {
        uv_close_cb uvCloseCb = [](uv_handle_t* handle) {
          qDebug()<<"closed"<<handle;
          if (handle != NULL)
            {
              free(handle);
              qDebug()<<"Freed"<<handle;
            }
        };
        uv_close(handle, uvCloseCb);
      };

      uv_walk(loop->uvHandle()
              , uvWalkCb
              , NULL);

      /*!
       * WARN: DON NOT TOUCH!!!
       * DATE: 9 Dec 2017 eoT3ohze
       *  - Only touch when crash on quit!!!
       *  - don't touch wait number, not sure how this works yet.
       *  - when wait < [longest timer delay] the chance of crash on quit is high.
       *  - related to kill wait of this thread and NetworkManager.
       */
      wait(2000);

      Parsley::Loop::defaultLoop()->run(UV_RUN_DEFAULT);
      result = loop->close();
      if (result)
        {
          qDebug() << "failed to close libuv loop: " << uv_err_name(result);
        }
      else
        {
          qDebug() << "libuv loop is closed successfully!\n";
        }
    }
  Log::net(Log::Normal, "UvServer::closeUvLoop()", "Successfully closed uv event loop.");
}

void
UvServer::sendTextMessage(const QJsonObject &msg, const BaseProtocol &protocol)
{
  switch (protocol) {
    case BaseProtocol::Udp:
      {
        QByteArray dat = encodeTextMessage(msg);
        uv_buf_t msg = uv_buf_init(dat.data(), dat.count());
//        udp_server->write("255.255.255.255", 23232, &msg);

        Log::net(Log::Normal, "UvServer::sendTextMessage()", "message sent");
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
UvServer::run()
{
  qDebug()<<"uv thread id: "<<this->currentThreadId();
  Log::net(Log::Normal, "UvServer::run()", "Thread Started");

  loop = Parsley::Loop::defaultLoop();
  udp_server = new HiveUdpServer(loop);
  udp_server->bindCb(std::bind(&UvServer::udpPacketReady
                               , this
                               , std::placeholders::_1
                               , std::placeholders::_2));
  udp_server->start();
  tcp_server = new Parsley::TcpServer("0.0.0.0", TCP_PORT, TCP_BACKLOG, loop);
  loop->run(UV_RUN_DEFAULT);

  Log::net(Log::Normal, "UvServer::run()", "Quit Thread");
}

void UvServer::udpPacketReady(const Parsley::Buffer &data, char *ip)
{
  NetPacket *packet = new NetPacket(ip, data.base, data.len, BaseProtocol::Udp);
  AppDataManager::pushInboundBuffer(packet);
}


bool
UvServer::processHeartBeat(const UsrProfileStruct &usrProfileStruct)
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
      Log::net(Log::Normal, "UvServer::processHeartBeat", "got heart beat from myself");
//      emit getInstance()->usrEntered(usrProfileStruct);
    }
  else
    {
      Log::net(Log::Normal, "UvServer::processHeartBeat", "got heart beat from others");
//      emit getInstance()->usrEntered(usrProfileStruct);
    }
}

bool
UvServer::processUsrLeave(QString *usrKey)
{
  if(*usrKey == Global::settings.profile_key_str)
    {
//      emit usrLeft(usrKey); << FIX HERE!!

      qDebug()<<"@UvServer::udpProcessUsrLeft(): Myself left.";
    }

  qDebug()<<"@UvServer::udpProcessUsrLeft(): Someone left.";
//  emit usrLeft(usrKey); << FIX HERE!!
}

bool
UvServer::processErrorDelivery()
{

}

bool
UvServer::processTextMessage()
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
UvServer::processFileInfo()
{

}

bool
UvServer::processFileContent()
{

}

bool
UvServer::processFileAccept()
{

}

bool
UvServer::processFileReject()
{

}














