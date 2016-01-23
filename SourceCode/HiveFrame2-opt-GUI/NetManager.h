#ifndef NETMANAGER_H
#define NETMANAGER_H

#include "GlobalData.h"

#include <QObject>
#include <QHostInfo>
#include <QString>
#include <QDataStream>
#include <QUdpSocket>
#include <QDateTime>
#include <QNetworkInterface>


enum BroadcastType{Message, UsrEnter, UsrLeft, FileName, Refuse};

/*

 Message : void sendMessage(QString ip_addr, QString message);

  */
class NetManager : public QObject
{
  Q_OBJECT

public:
  explicit NetManager(QObject *parent = 0);
  ~NetManager();

  void sendMessage(QString ip_addr, QString message);
  void sendUsrEnter();

  static void localHostIP();

private:
  qint16 udp_port = 23232;
  QUdpSocket *udp_socket;


public slots:
  void processPendingDatagrams();

signals:
  void messageRecieved(QStringList messageStrList);

};

#endif // NETMANAGER_H
