#ifndef HIVESERVER_H
#define HIVESERVER_H

#include "./Data/AppDataManager.h"

#include "HiveUdpServer.h"
#include "HiveProtocol.h"

#include <libparsley/tcp_server.h>
#include <libparsley/timer.h>
#include <libparsley/parsley.h>


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

#endif // HIVESERVER_H
