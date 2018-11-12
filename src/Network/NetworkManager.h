#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include "Global.h"
#include "GlobalType.h"
#include "HiveServer.h"
#include "Log.h"

#include <QThread>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkInterface>
#include <QDataStream>
#include <QDate>


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

  void udpSendMessage(const QJsonObject &jsonObj);

private:  
  void checkUpdate();
  void udpProcessUsrLeft(QString *usrKey);
  void udpProcessFileTran(const Message::TextMessage &fileInfoStruct);
  void udpProcessFileReject();

  HiveServer *uv_server;
  bool downloaded_update = false;
  QNetworkAccessManager *http_update_manager;
  QNetworkReply *http_update_reply;
  QByteArray http_update_file;

private:
  void onRedirectFinished();

signals:
  void messageRecieved(const Message::TextMessage &messageStruct, bool fromMe);//<
  void usrEnter(const UsrProfile &usrProfileStruct);
  void usrLeft(QString *usrKey);
  void updateAvailable();
};




#endif // NETWORKMANAGER_H
