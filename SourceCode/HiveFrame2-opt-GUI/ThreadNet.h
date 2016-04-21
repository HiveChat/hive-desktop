#ifndef THREADNET_H
#define THREADNET_H

#include "GlobalData.h"

#include <QThread>
#include <QHostInfo>
#include <QDataStream>
#include <QUdpSocket>
#include <QDateTime>
#include <QFile>
#include <QNetworkInterface>
#include <QPixmap>


class ThreadNet : public QThread
{
  Q_OBJECT
public:
  explicit ThreadNet(QObject *parent = 0);
  ~ThreadNet();

protected:
  void run();


private:
  enum BroadcastType{
    Message,
    UsrEnter,
    UsrLeft,
    FileName,
    Refuse
  };

  bool running = true;

  void setStatus(bool running);
  void refreshLocalHostIP();
  void sendOnlineStatus();

  qint16 udp_port = 23232;
  QUdpSocket *udp_socket;
  void processMessage(MessageStruct *messageStruct);
  void processUsrEnter(UsrProfileStruct *usrProfileStruct);
  void processUsrLeft(QString *usrKey);
  void processFileName();
  void processRefuse();



signals:
  void messageRecieved(QStringList messageStrList, bool fromMe);
  void usrEnter(UsrProfileStruct *usrProfileStruct);
  void usrLeft(QString *usrKey);

public slots:
  void sendUsrEnter();
  void sendMessage(QString usrKeyStr, QString message);
  void TEST_sendMessage(QString to, QString from, QString message);



private slots:
  void processPendingDatagrams();




};

#endif // THREADNET_H
