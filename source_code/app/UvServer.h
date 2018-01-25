#ifndef UVTCPSERVER_H
#define UVTCPSERVER_H

#define UDP_PORT 23232

#define TCP_PORT 23232
#define TCP_BACKLOG 128

#include "HiveProtocol.h"
#include "../libs/libParsley/src/PUdpSocket.h"
#include "../libs/libParsley/src/PTcpServer.h"

#include <QThread>
#include <QDebug>
#include <QHash>

#ifdef Q_OS_WIN
#include "../libs/libuv/win32/include/uv.h"
#else
#include <uv.h>
#endif

class UvServer;

class UvServer
    : public QThread
    , public HiveProtocol
{
  Q_OBJECT

public:
  enum BaseProtocol{
    Any = 0,
    Udp = 1,
    Tcp = 2
  };

  explicit UvServer(QObject *parent = 0);
  ~UvServer();

  void quit();
  void sendTextMessage(const QJsonObject &msg, const BaseProtocol &protocol = BaseProtocol::Udp);

protected:
  void run();

private:  
  static uv_loop_t *loop;
  static uv_timer_t *heart_beat_timer;
  static PTcpServer *tcp_server;
  static PUdpSocket *udp_server;

//  static void uvWalkCb(uv_handle_t* handle, void* arg);
//  static void uvCloseCb(uv_handle_t* handle);

  static void udpHeartBeatCb(uv_timer_t *handle);
  void udpReadyRead(char *data, char *ip);

  bool processHeartBeat(const UsrProfileStruct &usrProfileStruct);
  bool processUsrLeave(QString *usrKey);
  bool processErrorDelivery();
  bool processTextMessage();
  bool processFileInfo();
  bool processFileContent();
  bool processFileAccept();
  bool processFileReject();
};

#endif // UVTCPSERVER_H
