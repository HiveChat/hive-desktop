#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include "GlobalData.h"
#include "GlobalType.h"
#include "HiveServer.h"
#include "Log.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QThread>
#include <QHostInfo>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUdpSocket>
#include <QNetworkInterface>
#include <QDataStream>
#include <QFile>
#include <QDate>
#include <QTimer>


class NetworkManager : public QObject
{
  Q_OBJECT
public:
  explicit NetworkManager(QObject *parent = 0);
  ~NetworkManager();

  HiveServer *uv_server;


private:
  enum BroadcastType{
    Message = 1,
    HeartBeat = 2,
    UsrLeave = 3,
    FileTranReq = 4,
    FileReject = 5,
    File = 6,

  };

  enum NetworkError{
    NoError,
    NoInternet,
    NoNetwork,
    TimeOut
  };

  QHash<QString, QHostAddress> ip_address_hash;

  ///Thread Tasks
  bool downloaded_update = false;
  void checkUpdate();
  void loadTimerTasks();

  QNetworkAccessManager *http_update_manager;
  QNetworkReply *http_update_reply;
  QByteArray http_update_file;

  ///UDP Socket
  quint16 udp_port = 23232;
  QUdpSocket *udp_socket;
  void udpProcessMessage(const Message::TextMessage &messageStruct);
  void udpProcessHeartBeat(const UsrProfile &usrProfileStruct);
  void udpProcessUsrLeft(QString *usrKey);
  void udpProcessFileTran(const Message::TextMessage &fileInfoStruct);
  void udpProcessFileReject();

  void udpSendHeartBeat();
  void udpSendUsrLeave();
  void udpSendFileTran();
  void udpSendFileAccept();
  void TEST_udpsSendMessage(QString to, QString from, QString message);

  ///TCP Server
  qint16 tcp_port = 23232;
  QString file_name;
  QFile *local_file;


  void tcpCloseConnection();


public slots:
  void udpSendMessage(const QJsonObject &jsonObj);

private slots:
  void udpProcessPendingDatagrams();

  void tcpSendData();

  void onRedirectFinished();



signals:
  void messageReceived(const QJsonObject &jsonObj, const MessageType &msgType);

  void messageRecieved(const Message::TextMessage &messageStruct, bool fromMe);//<
  void usrEnter(const UsrProfile &usrProfileStruct);
  void usrLeft(QString *usrKey);

  void updateAvailable();

};




#endif // NETWORKMANAGER_H







