#ifndef HIVESERVER_H
#define HIVESERVER_H

#include "./Data/AppDataManager.h"

#include "HiveUdpServer.h"
#include "HiveProtocol.h"

#include <libagio/tcp_server.h>
#include <libagio/timer.h>
#include <libagio/agio.h>


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
  Agio::Loop *loop;
  Agio::TcpServer *tcp_server;
  HiveUdpServer *udp_server;
  Agio::Timer *heartbeat_timer;

  void udpPacketReady(std::string &data, Agio::HostAddress &ip);
  void onTimedOut(Agio::Timer *);

//  bool processUsrLeave(QString *usrKey); <<! to be moved to AppDataManager
};

#endif // HIVESERVER_H
