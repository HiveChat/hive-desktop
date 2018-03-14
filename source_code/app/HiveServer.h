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


class HiveServer;

class HiveServer final
    : public QThread
    , public HiveProtocol
{
  Q_OBJECT

public:
  explicit HiveServer(QObject *parent = 0);
  ~HiveServer();

  void quit();
  void sendTextMessage(const QJsonObject &msg, const BaseProtocol &protocol = BaseProtocol::Udp);

protected:
  void run();

private:  
  Parsley::Loop *loop;
  static Parsley::TcpServer *tcp_server;
  HiveUdpServer *udp_server;

  static int counter;

  void udpPacketReady(const Parsley::Buffer &data, char *ip);

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
