#ifndef UVTCPSERVER_H
#define UVTCPSERVER_H

#include "../libs/libParsley/src/PTcpServer.h"
#include "../libs/libParsley/src/PLoop.h"

#include "HiveProtocol.h"
#include "HiveUdpServer.h"
#include "./Data/AppDataManager.h"


#define UDP_PORT 23232

#define TCP_PORT 23232
#define TCP_BACKLOG 128


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
  static Parsley::TcpServer *tcp_server;
  HiveUdpServer *udp_server;

  static int counter;

  static void udpHeartBeatCb(uv_timer_t *handle);
  void udpPacketReady(const QJsonObject &obj);

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
