#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include "Global.h"
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

public:
  explicit NetworkManager(QObject *parent = nullptr);
  ~NetworkManager();

private:
  HiveServer *uv_server;

  bool downloaded_update = false;
  QNetworkAccessManager *http_update_manager;
  QNetworkReply *http_update_reply;
  QByteArray http_update_file;

  void checkUpdate();
  void udpProcessUsrLeft(QString *usrKey);
  void udpProcessFileTran(const Message::TextMessage &fileInfoStruct);
  void udpProcessFileReject();

public slots:
  void udpSendMessage(const QJsonObject &jsonObj);

private slots:
  void onRedirectFinished();

signals:
  void messageRecieved(const Message::TextMessage &messageStruct, bool fromMe);//<
  void usrEnter(const UsrProfile &usrProfileStruct);
  void usrLeft(QString *usrKey);
  void updateAvailable();

};




#endif // NETWORKMANAGER_H







