#include "NetworkManager.h"


NetworkManager::NetworkManager(QObject *parent) : QObject(parent)
{
  UvTcpServer *uv_tcp_server = new UvTcpServer(this);
  uv_tcp_server->start();
//  tcp_server = new TcpServer();
//  QThread *serverThread = new QThread(this);
//  tcp_server->moveToThread(serverThread);
//  serverThread->start();

//  tcp_server->start();

  udp_socket = new QUdpSocket(this);
  udp_socket->bind(udp_port, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);
  connect(udp_socket, SIGNAL(readyRead()), this, SLOT(udpProcessPendingDatagrams()));

  checkUpdate();
  loadTimerTasks();
}

NetworkManager::~NetworkManager()
{
  udpSendUsrLeave();
  qDebug()<<"NetworkManager destructed";
}

//void NetworkManager::refreshLocalHostIP()
//{
//  QList<QHostAddress> AddressList = QNetworkInterface::allAddresses();
//  QHostAddress result;
//  foreach(QHostAddress address, AddressList)
//    {
//      if(address.protocol() == QAbstractSocket::IPv4Protocol
//         && address != QHostAddress::Null
//         && address != QHostAddress::LocalHost)
//        {
//          if (!address.toString().contains("169.254."))
//            {
//              result = address;
//              break;
//            }
//        }
//    }

//  if(!result.isNull())
//    {
//      GlobalData::g_localHostIP = result.toString();
//    }
//  else
//    {
//      GlobalData::g_localHostIP = "";
//    }
//  qDebug()<<"@refreshLocalHostIP(): finished!";
//}

void NetworkManager::checkUpdate()
{
  http_update_manager = new QNetworkAccessManager(this);
  http_update_reply = http_update_manager->head(QNetworkRequest(GlobalData::update_url)); //leak?
  connect(http_update_reply, &QNetworkReply::finished,
          this, &NetworkManager::onRedirectFinished);
}

void NetworkManager::loadTimerTasks()
{
  udpSendHeartBeat();

  QTimer *timer_3s = new QTimer(this);
  connect(timer_3s, &QTimer::timeout,
          [this](){
            udpSendHeartBeat();
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
          qDebug()<<"@NetworkManager::udpProcessMessage(): Got msg I sent: "<<messageStruct.message;
          emit messageRecieved(messageStruct, true);
        }
    }
  else
    {
      if(messageStruct.sender == GlobalData::settings_struct.profile_key_str)
        {
          qDebug()<<"@NetworkManager::udpProcessMessage(): me 2 me...";
          emit messageRecieved(messageStruct, true);
        }
      else
        {
          qDebug()<<"@NetworkManager::udpProcessMessage(): Other people sent: "<<messageStruct.message;
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
      if(GlobalData::g_localHostIP != usrProfileStruct.ip)
        {
          GlobalData::g_localHostIP = usrProfileStruct.ip;
        }
      Log::net(Log::Normal, "NetworkManager::udpProcessHeartBeat()", "got heart beat from myself");
      emit usrEnter(usrProfileStruct);
    }
  else
    {
      Log::net(Log::Normal, "NetworkManager::udpProcessHeartBeat()", "got heart beat from others");
      emit usrEnter(usrProfileStruct);
    }

}

void NetworkManager::udpProcessUsrLeft(QString *usrKey)
{
  if(usrKey == GlobalData::settings_struct.profile_key_str)
    {
      emit usrLeft(usrKey);

      qDebug()<<"@NetworkManager::udpProcessUsrLeft(): Myself left.";
    }

  qDebug()<<"@NetworkManager::udpProcessUsrLeft(): Someone left.";
  emit usrLeft(usrKey);
}

void NetworkManager::udpProcessFileTran(const Message::FileInfoStruct &fileInfoStruct)
{
//  file_info_struct.index = json_obj.value("index");
//  file_info_struct.name = json_obj.value("name").toString();
//  file_info_struct.size = json_obj.value("size").toInt();
//  file_info_struct.type = (GUI::BuiltInIconType)json_obj.value("type").toInt();

}

///UDP Action
void NetworkManager::udpSendHeartBeat()
{
  QByteArray data;
  QDataStream out(&data, QIODevice::WriteOnly);

  QJsonObject json_obj;
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
      Log::net(Log::Normal, "NetworkManager::udpSendHeartBeat()", "heart beat sent");
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

  if(!GlobalData::online_usr_data_hash.contains(json_obj["receiver"].toString()))
    {
      Log::net(Log::Critical, "NetworkManager::udpSendMessage()", "sending to usr out of online_usr_data_hash failed!");
      return;
    }

  QString usrIp = GlobalData::online_usr_data_hash.value(json_obj["receiver"].toString())->ip();

  qint64 ret = udp_socket->writeDatagram(data
                                         , data.length()
                                         , usrIp.isEmpty() ? QHostAddress::Broadcast : QHostAddress(usrIp)
                                         , udp_port);
  if(ret != 0 && ret != -1)
    {
      qDebug()<<"@NetworkManager::udpSendMessage(): sent!";
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






void NetworkManager::tcpSendData()
{

}

void NetworkManager::onRedirectFinished()
{
  if(http_update_reply->error() != QNetworkReply::NoError)
    {
      Log::net(Log::Error, "NetworkManager::onRedirectFinished()", QString(http_update_reply->error()));
      return;
    }
  QUrl redirectUrl = QString(http_update_reply->rawHeader("Location"));

  Log::net(Log::Error, "NetworkManager::onRedirectFinished()", redirectUrl.toString());

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
                    if(/*memcmp(GlobalData::update_struct.version,
                              GlobalData::current_version,
                              sizeof(GlobalData::current_version)) != 0*/
                       GlobalData::versionCompare(GlobalData::update_struct.version, GlobalData::current_version))
                      {
                        Log::net(Log::Normal, "NetworkManager::onRedirectFinished()", "update available");
                        emit updateAvailable();
                      }
                    else
                      {
                        Log::net(Log::Normal, "NetworkManager::onRedirectFinished()", "version already new");
                      }
                  }
                else
                  {
                    Log::net(Log::Critical, "NetworkManager::onRedirectFinished()", "Update Json Document IS NOT AN OBJECT!");
                  }
              }
            else
              {
                Log::net(Log::Critical, "NetworkManager::onRedirectFinished()", "Update Json Document Parse ERROR!");
              }

            qDebug()<<"@NetworkManager: Got update file: "<<http_update_file;
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
      QHostAddress sender_address;
      udp_socket->readDatagram(datagram.data(), datagram.size(), &sender_address);
      QDataStream in(&datagram, QIODevice::ReadOnly);

      QByteArray byte_array;
      in >> byte_array;

      qDebug()<<byte_array;


      QJsonDocument json_document = QJsonDocument::fromJson(byte_array);
      if(json_document.isObject())
        {
          Log::net(Log::Normal, "NetworkManager::checkJsonObject()", "got message with JSON format");

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
                usr_profile.ip = sender_address.toString().remove("::ffff:");
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
            case FileTranReq:
              {
                Message::FileInfoStruct file_info_struct;
                file_info_struct.index = json_obj.value("index").toString();
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
            case File:
              {

                break;
              }
            }

        }
      else
        {
          qWarning()<<"@NetworkManager::checkJsonObject(): message crashed / message from old versions";
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
//                qDebug() << "@NetworkManager::checkJsonObject(): Json object crashed.";
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



