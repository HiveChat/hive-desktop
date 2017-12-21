#include "UvServer.h"


uv_loop_t* UvServer::loop;
TcpServer* UvServer::tcp_server;
UdpSocket* UvServer::udp_server;
uv_timer_t* UvServer::heart_beat_timer;


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
  int result = uv_loop_close(loop);
  if (result == UV_EBUSY)
    {
      uv_walk(loop, uvWalkCb, NULL);

      /// WARN: DON NOT TOUCH!!!
      /// DATE: 9 Dec 2017 eoT3ohze
      ///  - Only touch when crash on quit!!!
      ///  - don't touch wait number, not sure how this works yet.
      ///  - when wait < [longest timer delay] the chance of crash on quit is high.
      ///  - related to kill wait of this thread and NetworkManager.
      wait(2000);


      uv_run(uv_default_loop(), UV_RUN_DEFAULT);


      result = uv_loop_close(loop);
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
UvServer::uvWalkCb(uv_handle_t* handle, void* arg)
{
  uv_close(handle, uvCloseCb);

}

void
UvServer::uvCloseCb(uv_handle_t* handle)
{
  qDebug()<<"closed"<<handle;
  if (handle != NULL)
    {
      free(handle);
      qDebug()<<"Freed"<<handle;
    }
}

void
UvServer::sendTextMessage(const QJsonObject &msg, const BaseProtocol &protocol)
{
  switch (protocol) {
    case BaseProtocol::Udp:
      {
        uv_udp_send_t *req = (uv_udp_send_t*)malloc(sizeof(uv_udp_send_t));
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

  loop = uv_default_loop();

  udp_server = new UdpSocket("255.255,255,255", 23232, true, loop);
  qDebug()<<"udp"<<udp_server;
  tcp_server = new TcpServer("0.0.0.0", TCP_PORT, TCP_BACKLOG, loop);
  qDebug()<<"tcp"<<tcp_server;

  heart_beat_timer = (uv_timer_t*)malloc(sizeof(uv_timer_t));
  uv_timer_init(loop, heart_beat_timer);
  uv_timer_start(heart_beat_timer, udpHeartBeatCb, 1000, 2000);
  qDebug()<<"timer"<<heart_beat_timer;

  uv_run(loop, UV_RUN_DEFAULT);
  Log::net(Log::Normal, "UvServer::run()", "Quit Thread");
}

void
UvServer::udpHeartBeatCb(uv_timer_t *handle)
{
  QByteArray dat = encodeHeartBeat();
  uv_buf_t msg = uv_buf_init(dat.data(), dat.count());
  udp_server->write("255.255.255.255", 23232, &msg);

  Log::net(Log::Normal, "UvServer::udpHeartBeatCb()", "heart beat sent");
}
