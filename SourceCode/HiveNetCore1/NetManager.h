#ifndef NETMANAGER_H
#define NETMANAGER_H

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

public slots:
  void processPendingDatagrams();

private:
  qint16 udp_port = 23232;
  QUdpSocket *udp_socket;

signals:

public slots:
};

#endif // NETMANAGER_H
