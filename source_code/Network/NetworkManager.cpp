#include "NetworkManager.h"


NetworkManager::NetworkManager(QObject *parent) : QObject(parent)
{
  tcp_server = new QTcpServer(this);
  connect(tcp_server, SIGNAL(newConnection()), this, SLOT(tcpSendData()));
  tcpInitServer();

  udp_socket = new QUdpSocket(this);
  udp_socket->bind(udp_port, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);
  connect(udp_socket, SIGNAL(readyRead()), this, SLOT(udpProcessPendingDatagrams()));

  checkUpdate();
  loadTimerTasks();
}

NetworkManager::~NetworkManager()
{
  udpSendUsrLeave();
  qDebug()<<"ThreadNet destructed";
}

void NetworkManager::refreshLocalHostIP()
{
  QList<QHostAddress> AddressList = QNetworkInterface::allAddresses();
  QHostAddress result;
  foreach(QHostAddress address, AddressList)
    {
      if(address.protocol() == QAbstractSocket::IPv4Protocol
         && address != QHostAddress::Null
         && address != QHostAddress::LocalHost)
        {
          if (!address.toString().contains("127.0.")
              && !address.toString().contains("169.254."))
            {
              result = address;
              break;
            }
        }
    }

  if(!result.isNull())
    {
      GlobalData::g_localHostIP = result.toString();
    }
  else
    {
      GlobalData::g_localHostIP = "";
    }
  qDebug()<<"@refreshLocalHostIP(): finished!";
}

void NetworkManager::sendOnlineStatus()
{
  if(!GlobalData::g_localHostIP.isEmpty())
    {
      udpSendHeartBeat();
    }
}

void NetworkManager::checkUpdate()
{
  http_update_manager = new QNetworkAccessManager(this);
  http_update_reply = http_update_manager->head(QNetworkRequest(GlobalData::update_url)); //leak?
  connect(http_update_reply, &QNetworkReply::finished,
          this, &NetworkManager::onRedirectFinished);
}

void NetworkManager::loadTimerTasks()
{
  QTimer *timer_1s = new QTimer(this);
  connect(timer_1s, &QTimer::timeout,
          [this](){
            refreshLocalHostIP();
          });
  timer_1s->setSingleShot(false);
  timer_1s->start(1000);

  QTimer *timer_3s = new QTimer(this);
  connect(timer_3s, &QTimer::timeout,
          [this](){
            sendOnlineStatus();
          });
  timer_3s->setSingleShot(false);
  timer_3s->start(3000);
}

///udp process
void NetworkManager::udpProcessMessage(const Message::TextMessageStruct &messageStruct)
{
  if(messageStruct.sender.isEmpty() || messageStruct.reciever.isEmpty())
    {
      return;
    }

  if(messageStruct.reciever != GlobalData::settings_struct.profile_key_str)
    {
      if(messageStruct.sender != GlobalData::settings_struct.profile_key_str)
        {
          //no sniffing man!
          return;
        }
      else
        {
          qDebug()<<"@ThreadNet::udpProcessMessage(): Got msg I sent: "<<messageStruct.message;
          emit messageRecieved(messageStruct, true);
        }
    }
  else
    {
      if(messageStruct.sender == GlobalData::settings_struct.profile_key_str)
        {
          qDebug()<<"@ThreadNet::udpProcessMessage(): me 2 me...";
          emit messageRecieved(messageStruct, true);
        }
      else
        {
          qDebug()<<"@ThreadNet::udpProcessMessage(): Other people sent: "<<messageStruct.message;
          emit messageRecieved(messageStruct, false);
        }
    }
}

void NetworkManager::udpProcessHeartBeat(const UsrProfileStruct &usrProfileStruct)
{
  if(usrProfileStruct.key.isEmpty())
    {
      return;
    }

  if(usrProfileStruct.key == GlobalData::settings_struct.profile_key_str)
    {
      qDebug()<<"@ThreadNet::udpProcessHeartBeat(): Myself entered.";
      emit usrEnter(usrProfileStruct);
    }
  else
    {
      qDebug()<<"@ThreadNet::udpProcessHeartBeat(): Someone entered.";
      emit usrEnter(usrProfileStruct);
    }

}

void NetworkManager::udpProcessUsrLeft(QString *usrKey)
{
  if(usrKey == GlobalData::settings_struct.profile_key_str)
    {
      emit usrLeft(usrKey);

      qDebug()<<"@ThreadNet::udpProcessUsrLeft(): Myself left.";
    }

  qDebug()<<"@ThreadNet::udpProcessUsrLeft(): Someone left.";
  emit usrLeft(usrKey);
}

void NetworkManager::udpProcessFileTran(const Message::FileInfoStruct &fileInfoStruct)
{

}

///UDP Action
void NetworkManager::udpSendHeartBeat()
{
  QByteArray data;
  QDataStream out(&data, QIODevice::WriteOnly);

  QJsonObject json_obj;
  json_obj.insert("ip", GlobalData::g_localHostIP);
  json_obj.insert("key", GlobalData::settings_struct.profile_key_str);
  json_obj.insert("name", GlobalData::settings_struct.profile_name_str);
  json_obj.insert("avatar", GlobalData::settings_struct.profile_avatar_str);
  json_obj.insert("msgType", HeartBeat);
  QJsonDocument json_doc(json_obj);
  out << json_doc.toJson();
  qint64 ret = udp_socket->writeDatagram(data
                            , data.length()
                            , QHostAddress::Broadcast
                            , udp_port);
  if(ret != 0 && ret != -1)
    {
      qDebug()<<"@sendUsrEnter(): sent!";
    }

  return;
}

void NetworkManager::udpSendUsrLeave()
{
  QByteArray data;
  QDataStream out(&data, QIODevice::WriteOnly);
  out << UsrLeave << GlobalData::settings_struct.profile_key_str;
  udp_socket->writeDatagram(data
                            , data.length()
                            , QHostAddress::Broadcast
                            , udp_port);

  qDebug()<<"@sendUsrLeave(): Finished!";
}

void NetworkManager::udpSendMessage(const QJsonObject &jsonObj)
{
  QByteArray data;
  QDataStream out(&data, QIODevice::WriteOnly);

  QJsonObject json_obj = jsonObj;
  json_obj.insert("index", QJsonValue(GlobalData::getRandomString(8)));
  json_obj.insert("msgType", Message);
  QJsonDocument json_doc(json_obj);

  out << json_doc.toJson();
  qint64 ret = udp_socket->writeDatagram(data
                                         , data.length()
                                         , QHostAddress::Broadcast
                                         , udp_port);
  if(ret != 0 && ret != -1)
    {
      qDebug()<<"@ThreadNet::udpSendMessage(): sent!";
    }
}

void NetworkManager::udpSendFileTran()
{

}

void NetworkManager::udpSendFileAccept()
{

}

void NetworkManager::TEST_udpsSendMessage(QString to, QString from, QString message)
{
  QByteArray data;
  QDataStream out(&data, QIODevice::WriteOnly);

  if (message.isEmpty())
    {
      qDebug()<<"@sendMessage(): Message content empty!";
      return;
    }

  out << Message << to << from << message;
  udp_socket->writeDatagram(data,data.length(),QHostAddress::Broadcast, udp_port);
}



void NetworkManager::udpProcessFileReject()
{

}





void NetworkManager::tcpInitServer()
{

}

void NetworkManager::tcpSendData()
{

}

void NetworkManager::onRedirectFinished()
{
  QUrl redirectUrl = QString(http_update_reply->rawHeader("Location"));
  qDebug()<<"@ThreadNet::onRedirectFinished(): Redirect url from http header:"<<redirectUrl.toString();

  http_update_manager->deleteLater();
  http_update_reply->deleteLater();

  http_update_manager = new QNetworkAccessManager(this);
  http_update_reply = http_update_manager->get(QNetworkRequest(redirectUrl));

  connect(http_update_reply, &QNetworkReply::readyRead,
          [this]() {
            http_update_file.append(http_update_reply->readAll());
          });
  connect(http_update_reply, &QNetworkReply::finished,
          [this]() {
            qDebug()<<"Downloaded: "<<http_update_file;
            QJsonParseError json_error;
            QJsonDocument json_document = QJsonDocument::fromJson(http_update_file, &json_error);
            if(json_error.error == QJsonParseError::NoError)
              {
                if(json_document.isObject())
                  {
                    QJsonObject json_obj = json_document.object();
                    GlobalData::update_struct.version[0] = json_obj.value("stable_version").toInt();
                    GlobalData::update_struct.version[1] = json_obj.value("beta_version").toInt();
                    GlobalData::update_struct.version[2] = json_obj.value("alpha_version").toInt();
                    GlobalData::update_struct.message = json_obj.value("message").toString();
                    GlobalData::update_struct.title = json_obj.value("title").toString();
                    if(memcmp(GlobalData::update_struct.version,
                              GlobalData::current_version,
                              sizeof(GlobalData::current_version)) != 0)
                      {
                        qDebug()<<"@ThreadNet::onRedirectFinished(): update available";
                        emit updateAvailable();
                      }
                    else
                      {
                        qDebug()<<"@ThreadNet::onRedirectFinished(): already the newest version";
                      }
                  }
                else
                  {
                    qDebug()<<"!@ThreadNet::onRedirectFinished(): Update Json Document IS NOT AN OBJECT!";
                  }
              }
            else
              {
                qDebug()<<"!@ThreadNet::onRedirectFinished(): Update Json Document Parse ERROR!";
              }

            qDebug()<<"@ThreadNet: Got update file: "<<http_update_file;
            http_update_manager->deleteLater();
            http_update_reply->deleteLater();
          });
}

void NetworkManager::tcpCloseConnection()
{

}

void NetworkManager::udpProcessPendingDatagrams()
{
  while(udp_socket->hasPendingDatagrams())
    {
      QByteArray datagram;
      datagram.resize(udp_socket->pendingDatagramSize());
      udp_socket->readDatagram(datagram.data(), datagram.size());
      QDataStream in(&datagram, QIODevice::ReadOnly);

      QByteArray byte_array;
      in >> byte_array;

      ///new message data structure
      QJsonDocument json_document = QJsonDocument::fromJson(byte_array);
      if(json_document.isObject())
        {
          qDebug() << "@ThreadNet::checkJsonObject(): got message with JSON format";

          QJsonObject json_obj = json_document.object();
          int type = json_obj.value("msgType").toInt();

          switch (type) {
            case Message:
              {
                Message::TextMessageStruct message;
                message.index = json_obj.value("index").toString();
                message.time = json_obj.value("time").toString();
                message.reciever = json_obj.value("receiver").toString();
                message.sender = json_obj.value("sender").toString();
                message.message = json_obj.value("message").toString();
                udpProcessMessage(message);
                break;
              }
            case HeartBeat:
              {
                UsrProfileStruct usr_profile;
                usr_profile.ip = json_obj.value("ip").toString();
                usr_profile.key = json_obj.value("key").toString();
                usr_profile.name = json_obj.value("name").toString();
                usr_profile.avatar = json_obj.value("avatar").toString();
                udpProcessHeartBeat(usr_profile);
                break;
              }
            case UsrLeave:
              {

                break;
              }
            case FileTran:
              {
                Message::FileInfoStruct file_info_struct;
                file_info_struct.name = json_obj.value("name").toString();
                file_info_struct.size = json_obj.value("size").toInt();
                file_info_struct.type = (GUI::BuiltInIconType)json_obj.value("type").toInt();
                udpProcessFileTran(file_info_struct);
                break;
              }
            case FileReject:
              {

                break;
              }
            }

        }
      else
        {
          qWarning()<<"@ThreadNet::checkJsonObject(): message crashed / message from old versions";
        }
    }


//      int msgType;
//      in >> msgType;

//      switch(msgType)
//      {
//        case Message:
//          {
//            QByteArray byte_array;
//            in >> byte_array;

//            QJsonDocument json_document = QJsonDocument::fromBinaryData(byte_array);
//            if(!json_document.isObject())
//              {
//                qDebug() << "@ThreadNet::checkJsonObject(): Json object crashed.";
//                return;
//              }

//            QJsonObject json_obj = json_document.object();

//            Message::TextMessageStruct message;
//            message.index = json_obj.value("index").toString();
//            message.reciever = json_obj.value("receiver").toString();
//            message.sender = json_obj.value("sender").toString();
//            message.message = json_obj.value("message").toString();
//            message.time = json_obj.value("time").toString();

//            udpProcessMessage(&message);

//            break;
//          }
//        case UsrEnter:
//          {
//            UsrProfileStruct usr_profile;
//            in >> usr_profile.ip_str;
//            in >> usr_profile.key_str;
//            in >> usr_profile.name_str;
//            in >> usr_profile.avatar_str;

//            udpProcessUsrEnter(&usr_profile);
//            break;
//          }
//        case UsrLeave:
//          {


//          }
//        case FileReject:
//          {


//          }
//        case FileTran:
//          {
//            Message::FileInfoStruct file_info_struct;
//            in >> file_info_struct.name;
//            in >> file_info_struct.size;
//            in >> file_info_struct.type;

//            udpProcessFileTran(file_info_struct);
//            break;
//          }
//      }
//    }
}



