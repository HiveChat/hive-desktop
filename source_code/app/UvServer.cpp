#include "UvServer.h"

#include <QThread>

uv_loop_t* UvServer::loop;
Parsley::TcpServer* UvServer::tcp_server;
Parsley::UdpSocket* UvServer::udp_server;
uv_timer_t* UvServer::heart_beat_timer;
int UvServer::counter = 0;



UvServer::UvServer(QObject *parent)
  : QThread(parent)
{
}

UvServer::~UvServer()
{

}

void
UvServer::quit()
{
  int result = Parsley::Loop::close(loop);
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

      uv_walk(loop
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

      Parsley::Loop::run(Parsley::Loop::defaultLoop(), UV_RUN_DEFAULT);
      result = Parsley::Loop::close(loop);
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
        udp_server->write("255.255.255.255", 23232, &msg);

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

  udp_server = new Parsley::UdpSocket("255.255,255,255", UDP_PORT, loop);
  qDebug()<<"udp"<<udp_server;
  tcp_server = new Parsley::TcpServer("0.0.0.0", TCP_PORT, TCP_BACKLOG, loop);
  qDebug()<<"tcp"<<tcp_server;

  heart_beat_timer = (uv_timer_t*)malloc(sizeof(uv_timer_t));
  uv_timer_init(loop, heart_beat_timer);
  uv_timer_start(heart_beat_timer, udpHeartBeatCb, 1000, 1000);
  qDebug()<<"timer"<<heart_beat_timer;

  uv_timer_t *heart_beat_timer2 = (uv_timer_t*)malloc(sizeof(uv_timer_t));
  uv_timer_init(loop, heart_beat_timer2);
  uv_timer_start(heart_beat_timer2, [](uv_timer_t *handle){
    qDebug()<<counter << "p/s";
    counter = 0;
  }, 10, 1000);

//  uv_idle_t* idler = (uv_idle_t*) malloc(sizeof(uv_idle_t));
//  uv_idle_init(loop, idler);
//  uv_idle_start(idler, [](uv_idle_t* handle){
//    qDebug()<<"hello1 b";
//    sleep(1);
//    qDebug()<<"hello1 f";
//  });

//  uv_idle_t* idler2 = (uv_idle_t*) malloc(sizeof(uv_idle_t));
//  uv_idle_init(loop, idler2);
//  uv_idle_start(idler2, [](uv_idle_t* handle){
//    qDebug()<<"hello2 b";
//    sleep(1);
//    qDebug()<<"hello2 f";
//  });

  udp_server->bindCb(std::bind(&UvServer::udpReadyRead
                               , this
                               , std::placeholders::_1
                               , std::placeholders::_2));

  uv_run(loop, UV_RUN_DEFAULT);
  Log::net(Log::Normal, "UvServer::run()", "Quit Thread");
}

void
UvServer::udpHeartBeatCb(uv_timer_t *handle)
{
  QByteArray dat = encodeHeartBeat();
  uv_buf_t msg = uv_buf_init(dat.data(), dat.count());
  udp_server->write("255.255.255.255", UDP_PORT, &msg);

  counter ++;

  Log::net(Log::Normal, "UvServer::udpHeartBeatCb()", "heart beat sent");
}

void UvServer::udpReadyRead(char *data, char *ip)
{
  checkJson(QString(data), QString(ip));
//  emit usrEntered(decodeHivePacket);
//  qDebug()<<data;
}


bool
UvServer::processHeartBeat(const UsrProfileStruct &usrProfileStruct)
{
  if(usrProfileStruct.key.isEmpty())
    {
      return false;
    }

  if(usrProfileStruct.key == GlobalData::settings_struct.profile_key_str)
    {
      if(GlobalData::g_localHostIP != usrProfileStruct.ip)
        {
          GlobalData::g_localHostIP = usrProfileStruct.ip;
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
  if(*usrKey == GlobalData::settings_struct.profile_key_str)
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














