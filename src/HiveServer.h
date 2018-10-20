#ifndef UVTCPSERVER_H
#define UVTCPSERVER_H

#include "../libs/libParsley/include/PTcpServer.h"
#include "../libs/libParsley/include/Parsley.h"

#include "HiveProtocol.h"
#include "HiveUdpServer.h"
#include "./Data/AppDataManager.h"


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

  void stop();
  void sendTextMessage(const QJsonObject &msg, const BaseProtocol &protocol = BaseProtocol::Udp);

protected:
  void run();

private:  
  Parsley::Loop *loop;
  Parsley::TcpServer *tcp_server;
  HiveUdpServer *udp_server;

  static int counter;

  void udpPacketReady(Parsley::Buffer *data, char *ip);

  bool processHeartBeat(const UsrProfile &usrProfileStruct);
  bool processUsrLeave(QString *usrKey);
  bool processErrorDelivery();
  bool processTextMessage();
  bool processFileInfo();
  bool processFileContent();
  bool processFileAccept();
  bool processFileReject();
};

#endif // UVTCPSERVER_H
