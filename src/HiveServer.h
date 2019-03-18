#ifndef UVTCPSERVER_H
#define UVTCPSERVER_H

#include "libparsley/tcp_server.h"
#include "libparsley/timer.h"
#include "libparsley/parsley.h"

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
  explicit HiveServer(QObject *parent = nullptr);
  ~HiveServer();

  void stop();
  void sendTextMessage(const QJsonObject &msg, const BaseProtocol &protocol = BaseProtocol::Udp);

protected:
  void run();

private:  
  Parsley::Loop *loop;
  Parsley::TcpServer *tcp_server;
  HiveUdpServer *udp_server;
  Parsley::Timer *heartbeat_timer;

  void udpPacketReady(std::string &data, Parsley::IPAddress &ip);
  void onTimedOut(Parsley::Timer *);

//  bool processUsrLeave(QString *usrKey); <<! to be moved to AppDataManager

};

#endif // UVTCPSERVER_H
