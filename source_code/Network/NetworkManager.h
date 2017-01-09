#ifndef THREADNET_H
#define THREADNET_H

#include "GlobalData.h"
#include "GlobalType.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QThread>
#include <QHostInfo>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QTcpServer>
#include <QTcpSocket>
#include <QUdpSocket>
#include <QNetworkInterface>
#include <QDataStream>
#include <QFile>
#include <QDate>
#include <QMutex>


class NetworkManager : public QObject
{
  Q_OBJECT
public:
  explicit NetworkManager(QObject *parent = 0);
  ~NetworkManager();

private:
  enum BroadcastType{
    Message,
    HeartBeat,
    UsrLeave,
    FileTran,
    FileReject
  };

  enum NetworkError{
    NoError,
    NoInternet,
    NoNetwork,
    TimeOut
  };

  ///Thread Tasks
  bool downloaded_update = false;
  void refreshLocalHostIP();
  void sendOnlineStatus();
  void checkUpdate();
  void loadTimerTasks();


  QNetworkAccessManager *http_update_manager;
  QNetworkReply *http_update_reply;
  QByteArray http_update_file;

  ///UDP Socket
  quint16 udp_port = 23232;
  QUdpSocket *udp_socket;
  void udpProcessMessage(const Message::TextMessageStruct &messageStruct);
  void udpProcessHeartBeat(const UsrProfileStruct &usrProfileStruct);
  void udpProcessUsrLeft(QString *usrKey);
  void udpProcessFileTran(const Message::FileInfoStruct &fileInfoStruct);
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

  QTcpServer *tcp_server;
  QTcpSocket *tcp_socket;

  void tcpInitServer();
  void tcpCloseConnection();


public slots:
  void udpSendMessage(const QJsonObject &jsonObj);

private slots:
  void udpProcessPendingDatagrams();

  void tcpSendData();

  void onRedirectFinished();



signals:
  void messageReceived(const QJsonObject &jsonObj, const Message::MessageType &messageType);

  void messageRecieved(const Message::TextMessageStruct &messageStruct, bool fromMe);//<
  void usrEnter(const UsrProfileStruct &usrProfileStruct);
  void usrLeft(QString *usrKey);

  void updateAvailable();

};




#endif // THREADNET_H







