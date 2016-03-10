#ifndef NETMANAGER_H
#define NETMANAGER_H

#include "GlobalData.h"

#include <QObject>
#include <QHostInfo>
#include <QString>
#include <QDataStream>
#include <QUdpSocket>
#include <QDateTime>
#include <QFile>
#include <QNetworkInterface>
#include <QPixmap>


/*

 Message : void sendMessage(QString ip_addr, QString message);

  */
class NetManager : public QObject
{
  Q_OBJECT

public:
  explicit NetManager(QObject *parent = 0);
  ~NetManager();

  void sendUsrEnter();

  static void refreshLocalHostIP();

  void TEST();

private:
  qint16 udp_port = 23232;
  QUdpSocket *udp_socket;

  enum BroadcastType{Message, UsrEnter, UsrLeft, FileName, Refuse};

public slots:
  void sendMessage(QString usrKeyStr, QString message);
  void processPendingDatagrams();

  void TEST_sendMessage(QString to, QString from, QString message);

signals:
  void messageRecieved(QStringList messageStrList, bool fromMe);
  void usrEnter(QStringList usrInfoStrList);

//  usrKey<<usrName<<ipAddr<<avatarPath


};

#endif // NETMANAGER_H
