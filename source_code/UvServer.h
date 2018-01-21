#ifndef UVTCPSERVER_H
#define UVTCPSERVER_H

#define UDP_PORT 23232

#define TCP_PORT 23232
#define TCP_BACKLOG 128

#include "HiveProtocol.h"
#include "uv_udp_sock.h"
#include "TcpServer.h"

#include <QThread>
#include <QDebug>
#include <QHash>

#ifdef Q_OS_WIN
#include "../dependency/win32/libuv/include/uv.h"
#else
#include <uv.h>
#endif

class UvServer;

class UvServer
    : public QThread
    , public HiveProtocol
{
  Q_OBJECT

  typedef int SocketDescriptor;
  typedef struct {
    uv_write_t req;
    uv_buf_t buf;
  } write_req_t;

public:
  explicit UvServer(QObject *parent = 0);
  ~UvServer();

   void quit();

  void sendTextMessage(const QJsonObject &msg, const BaseProtocol &protocol = BaseProtocol::Udp);

protected:
  void run();

private:  
  static uv_loop_t *loop;
  static uv_timer_t *heart_beat_timer;
  static TcpServer *tcp_server;
  static UvUdpSock *udp_server;

  static void uvWalkCb(uv_handle_t* handle, void* arg);
  static void uvCloseCb(uv_handle_t* handle);

  static void udpHeartBeatCb(uv_timer_t *handle);


  void udpReadyRead(char *data, char *ip);

};

#endif // UVTCPSERVER_H
