#include "AppDataManager.h"

HiveDoubleBuffer<NetPacket*> AppDataManager::inboundNetBuffer;
HiveDoubleBuffer<NetPacket*> AppDataManager::outboundNetBuffer;

QHash<QString, UsrData*> AppDataManager::usr_data_hash;


std::map<QString, int*> AppDataManager::settings_int_hash;
std::map<QString, QColor*> AppDataManager::settings_qcolor_hash;
std::map<QString, QString*> AppDataManager::settings_qstring_hash;
std::map<QString, bool*> AppDataManager::settings_bool_hash;

AppDataManager::AppDataManager(QObject *parent)
  : QThread(parent)
{
}

AppDataManager::~AppDataManager()
{
  Log::gui(Log::Info, "AppDataManager::~AppDataManager()", "Successfully destroyed AppDataManager...");
}

void AppDataManager::stop()
{
  loop->close();
  Log::net(Log::Info, "AppDataManager::stop()", "Successfully closed uv event loop.");
}

void AppDataManager::pushInboundBuffer(NetPacket *packet)
{
  inboundNetBuffer.push_front(packet);
}

void AppDataManager::pushOutboundBuffer(NetPacket *packet)
{
  outboundNetBuffer.push_front(packet);
}

bool AppDataManager::isUsrNew(const QString &uuid)
{
  return !usr_data_hash.contains(uuid);
}

void AppDataManager::checkSettings()
{
  if(Global::settings.modified)
    {
      Log::dat(Log::Info, "AppDataManager::checkSettings()", "Settings changed.");
      writeSettings();
      Global::settings.modified = false;
    }
}

QJsonDocument AppDataManager::makeUpdateJson(const int version[])
{
  QJsonObject obj;
  obj.insert("stable_version", QJsonValue(version[0]));
  obj.insert("beta_version", QJsonValue(version[1]));
  obj.insert("alpha_version", QJsonValue(version[2]));

  QJsonDocument doc;
  doc.setObject(obj);
  return doc;
}

void AppDataManager::updateUsr(const UsrProfile &usrProfileStruct)
{
  QString uuid = usrProfileStruct.key;
  QString ipAddr = usrProfileStruct.ip;
  QString usrName = usrProfileStruct.name;
  QString avatarPath = usrProfileStruct.avatar;

  Parsley::File file(Global::contacts_file_dir, loop);
  if(!file.open(O_RDWR | O_CREAT, 0755, Parsley::SyncMode))
    {
      return;
    }
  std::string data = file.readAll();
  QJsonParseError jsonError;
  QJsonDocument inJsonDoc = QJsonDocument::fromJson(QByteArray(data.data(), data.size()), &jsonError);
  if(jsonError.error == QJsonParseError::NoError)
    {
      if(inJsonDoc.isObject())
        {
          QJsonObject usrListObj = inJsonDoc.object();
          QJsonObject usrInfoObj;
          usrInfoObj.insert("usrKey", uuid);
          usrInfoObj.insert("usrName", usrName);
          usrInfoObj.insert("avatarPath", avatarPath);
          if(!usrListObj.contains(uuid))
            {
              usrListObj.insert(uuid, usrInfoObj);

              QJsonDocument outJsonDoc;
              outJsonDoc.setObject(usrListObj);

              std::string data = outJsonDoc.toJson().toStdString();
              file.write(data, Parsley::SyncMode);
            }
          else
            {
              if(usrListObj[uuid] != usrInfoObj)
                {
                  usrListObj.remove(uuid);
                  usrListObj.insert(uuid, usrInfoObj);

                  QJsonDocument outJsonDoc;
                  outJsonDoc.setObject(usrListObj);

                  std::string data = outJsonDoc.toJson().toStdString();
                  file.write(data, Parsley::SyncMode);
                }
            }
        }
    }
  else
    {
      QJsonObject usrInfoObj;
      usrInfoObj.insert("usrKey", uuid);
      usrInfoObj.insert("usrName", usrName);
      usrInfoObj.insert("avatarPath", avatarPath);

      QJsonObject usrListObj;
      usrListObj.insert(uuid, usrInfoObj);

      QJsonDocument outJsonDoc;
      outJsonDoc.setObject(usrListObj);

      std::string data = outJsonDoc.toJson(QJsonDocument::Indented).toStdString();
      file.write(data, Parsley::SyncMode);
    }

  file.close(Parsley::SyncMode);
}

//!! OBSOLETE !!
void AppDataManager::deleteUsr(const QStringList usrInfoStrList)
{
//  QFile file(GlobalData::contacts_file_dir);
//  if(!file.open(QIODevice::ReadWrite | QIODevice::Text))
//  {
//    return;
//  }

//  QTextStream in(&file);
//  QTextStream out(&file);

//  QByteArray in_byte_array = in.readAll().toUtf8();

//  ///JSon
//  QJsonParseError json_error;
//  QJsonDocument readJsonDocument = QJsonDocument::fromJson(in_byte_array, &json_error);
//  if(json_error.error == QJsonParseError::NoError)
//    {
//      if(readJsonDocument.isObject())
//        {
//          QJsonObject usrListJsonObj = readJsonDocument.object();
//          usrListJsonObj.erase(usrListJsonObj.find(usrInfoStrList.at(0)));

//          QJsonDocument writeJsonDocument;
//          writeJsonDocument.setObject(usrListJsonObj);
//          file.resize(0);
//          out<<writeJsonDocument.toJson(QJsonDocument::Indented)<<endl;

//        }
//    }
//  else
//    {
//      qDebug()<<"Contact delete failed, is file empty?";

//    }

//  file.close();
//  file.flush();
}

//! TODO: PLEASE REVIEW AND REWRITE
void AppDataManager::onUsrEntered(UsrProfile &usrProfile) // logic problem here? too complicated?
{
  if(isUsrNew(usrProfile.key))
    {
      Log::dat(Log::Info, "DataManager::onUsrEntered()", "New user");
      usrProfile.online = true;
      UsrData *userData = new UsrData(&Global::settings.profile_key_str, usrProfile, this);
      usr_data_hash.insert(usrProfile.key, userData);
      updateUsr(usrProfile);
      emit usrProfileLoaded(userData);
    }
  else
    {
      UsrData *userData = usr_data_hash.value(usrProfile.key);
      qDebug()<<userData->getKey();
      if(usrProfile != *userData->getUsrProfileStruct())
        {
          userData->setUsrProfileStruct(usrProfile);
          emit usrProfileChanged(userData);
          Log::dat(Log::Info, "DataManager::onUsrEntered()", "user profile changed");
        }

    }


//  if(Global::online_usr_data_hash.contains(usrProfile.key))
//    {
//      Log::dat(Log::Info, "DataManager::onUsrEntered()", "incoming user already exist in online list");
//      UsrData *usrData = Global::online_usr_data_hash.value(usrProfile.key);
//      if(usrProfile != *usrData->getUsrProfileStruct())
//        {
//          usrData->setUsrProfileStruct(usrProfile);
//          emit usrProfileChanged(usrData);
//          Log::dat(Log::Info, "DataManager::onUsrEntered()", "user profile changed");
//        }
//    }
//  else if(Global::offline_usr_data_hash.contains(usrProfile.key))
//    {
//      Log::dat(Log::Info, "DataManager::onUsrEntered()", "incoming user already exist in offline list");
//      Global::online_usr_data_hash.insert(usrProfile.key, Global::offline_usr_data_hash.value(usrProfile.key));
//      UsrData *usrData = Global::online_usr_data_hash.value(usrProfile.key);
//      if(usrProfile != *usrData->getUsrProfileStruct())
//        {
//          usrData->setUsrProfileStruct(usrProfile);
//          updateUsr(usrProfile);
//          emit usrProfileChanged(usrData);
//          Log::dat(Log::Info, "DataManager::onUsrEntered()", "user profile changed");
//        }
//    }
//  else
//    {
//      UsrData *userData = new UsrData(&Global::settings.profile_key_str, usrProfile, this);
//      Global::online_usr_data_hash.insert(usrProfile.key, userData);
//      updateUsr(usrProfile);
//      emit usrProfileLoaded(userData);
//      qDebug()<<"@DataManager::onUsrEntered: User profile Created.";

//    }
}

void AppDataManager::onUsrLeft(QString *usrKey)
{

}

void AppDataManager::onMessageCome(const Message::TextMessage &messageStruct, bool fromMe)
{
  if(fromMe)
    {
      qDebug()<<"fromme";
      usr_data_hash.value(messageStruct.reciever)->addUnreadMessage(messageStruct);
    }
  else
    {
      qDebug()<<"notfromme";
      usr_data_hash.value(messageStruct.sender)->addUnreadMessage(messageStruct);
    }
  emit messageLoaded(messageStruct, fromMe);
}

void AppDataManager::onUpdatesAvailable()
{
  if(Global::update_struct.version[0] == 0
     && Global::update_struct.version[1] == 0
     && Global::update_struct.version[2] == 0)
    {
      return;
    }

  int outVersion[3];
  memcpy(&outVersion, &Global::current_version, sizeof(Global::current_version));

  Parsley::File file(Global::update_file_dir, loop);
  if(!file.open(O_RDWR | O_CREAT, 0755, Parsley::SyncMode))
    {
      return;
    }
  std::string inData = file.readAll();
  QJsonParseError jsonError;
  QJsonDocument inJsonDoc = QJsonDocument::fromJson(QByteArray(inData.data(), inData.size()), &jsonError);
  if(jsonError.error == QJsonParseError::NoError)
    {
      if(inJsonDoc.isObject())
        {
          QJsonObject inObj = inJsonDoc.object();

          int inVersion[3] = {
            inObj.value("stable_version").toInt(),
            inObj.value("beta_version").toInt(),
            inObj.value("alpha_version").toInt()
          };

          for(int i = 0; i < 3; i ++)
            {
              outVersion[i] = inVersion[i];
            }

          if(memcmp(inVersion,
                    Global::update_struct.version,
                    sizeof(inVersion)) == 0)
            {
              file.close(Parsley::SyncMode);
              emit updatesAvailable();

              return;
            }
          else
            {
              if(Global::versionCompare(Global::update_struct.version, inVersion))
                {
                  for(int i = 0; i < 3; i ++)
                    {
                      outVersion[i] = Global::update_struct.version[i];
                    }
                }
            }
        }
    }


  std::string outData = makeUpdateJson(outVersion).toJson(QJsonDocument::Indented).toStdString();
  file.write(outData, Parsley::SyncMode);
  file.close(Parsley::SyncMode);

  emit updatesAvailable();
}

void AppDataManager::run()
{
  initVariable();

  loop = new Parsley::Loop();

  inboundNetBuffer.bindCb(std::bind(&AppDataManager::wakeLoop, this, std::placeholders::_1));

  read_inbound_async = new Parsley::Async(loop);
  read_inbound_async->bindCb(std::bind(&AppDataManager::readInboundNetBuffer, this));

  touchDir(Global::data_location_dir);
  touchDir(Global::user_data_dir);
  touchDir(Global::log_dir);
  touchFile(Global::settings_file_dir);
  Parsley::File file1(Global::settings_file_dir, loop);
  file1.open(O_RDWR | O_CREAT, 0755, Parsley::SyncMode);
  file1.close(Parsley::SyncMode);

  loadSettings();
  loadUsrList();

  Parsley::Timer checkSettingsTimer(loop);
  checkSettingsTimer.bindCb(std::bind(&AppDataManager::checkSettings, this));
  checkSettingsTimer.start(2000, 1000);

  loop->run(UV_RUN_DEFAULT);
}

void AppDataManager::readInboundNetBuffer()
{
  inboundNetBufferReading = true;
  NetPacket *p = inboundNetBuffer.front();
  Log::net(Log::Info, "AppDataManager::readInboundNetBuffer()","Checking Package");

  while (p)
    {
      //! See if JSON object is complete.
      QJsonParseError err;
      QJsonDocument doc = QJsonDocument::fromJson(QByteArray(p->data, p->len), &err);
      QString ipAddr = QString::fromStdString(p->ipAddr);
      //! HiveDoubleBuffer calls std::list::pop_front(), which automatically calls destructor of NetPacket *p.
      inboundNetBuffer.pop_front();
      if(err.error != QJsonParseError::NoError || !doc.isObject())
        {
          Log::net(Log::Warning, "AppDataManager::readInboundNetBuffer()","emit");

          continue;
        }

      //! See if the package is delivered to me.
      QJsonObject packetJson = doc.object();
      QString receiverKey = packetJson.value("receiver").toString();
      if(receiverKey != Global::settings.profile_key_str
         && receiverKey != BROADCAST_UUID)
        {
          Log::net(Log::Warning
                   , "AppDataManager::readInboundNetBuffer()"
                   , "Package wrong destination: " + receiverKey + " My Id: " + Global::settings.profile_key_str);
          continue;
        }

      //! Start processing message
      MessageType messageType = (MessageType) packetJson.value("msgType").toInt();
      switch (messageType) {
        case MessageType::HeartBeat:
          {
            UsrProfile usr_profile;
            usr_profile.ip = ipAddr;
            usr_profile.key = packetJson.value("sender").toString();
            usr_profile.name = packetJson.value("name").toString();
            usr_profile.avatar = packetJson.value("avatar").toString();
            onUsrEntered(usr_profile);
            break;
          }
        case MessageType::TextMessage:
          {
    //        processTextMessage();
            break;
          }
        case MessageType::FileInfo:
          {
            Log::net(Log::Info, "HiveProtocol::decodeHivePacket()", "File info received.");

            break;
          }
        case MessageType::FileContent:
          {

            break;
          }
        case MessageType::FileReject:
          {

            break;
          }
        case MessageType::FileAccept:
          {

            break;
          }
        case MessageType::ErrorDelivery:
          {

            break;
          }
      }

      //! Get a new p.
      p = inboundNetBuffer.front();
    }
  inboundNetBufferReading = false;
}

void AppDataManager::wakeLoop(HiveDoubleBuffer<NetPacket *> *buf)
{
  if(!inboundNetBufferReading)
    read_inbound_async->send();
}

bool AppDataManager::touchFile(const std::string &path)
{
  Parsley::File f(path, loop);
  int ret = f.open(O_WRONLY | O_CREAT, 0644, Parsley::SyncMode);
  f.close(Parsley::SyncMode);
  return ret;
}

bool AppDataManager::touchDir(const std::string &dir)
{
  return Parsley::File::mkdir(dir, 0755, loop, Parsley::SyncMode) == 0;
}

QJsonDocument AppDataManager::makeDefaultSettings()
{
  Global::settings.profile_key_str = makeUuid();
  Global::settings.profile_avatar_str = ":/avatar/avatar/default.png";
  Global::settings.profile_name_str = QHostInfo::localHostName();


  QJsonObject obj;
  obj.insert("usrKey", Global::settings.profile_key_str);
  obj.insert("usrName", Global::settings.profile_name_str);
  obj.insert("avatarPath", Global::settings.profile_avatar_str);
  obj.insert("BubbleColorI", Global::color_defaultChatBubbleI.name());
  obj.insert("BubbleColorO", Global::color_defaultChatBubbleO.name());

  ////these default data will be integrated in a class[I don't know what I meat in this comment...]

  QJsonDocument doc;
  doc.setObject(obj);

  return doc;
}

QString AppDataManager::makeUuid()
{
  return QUuid::createUuid().toString();
}

void AppDataManager::initVariable()
{
  /*! 1. When adding global variable to settings, choose a map with corresponding data type below.
   *  2. When adding new types, you need to add corresponding maps for that type.
   *  Go to register in AppDataManager::readSettings() and AppDataManager::writeSettings() to enable reading and writing from disk.
   */
  settings_int_hash = {
    { "window_width", &Global::settings.window_width },
    { "window_height", &Global::settings.window_height }
  };

  settings_qcolor_hash = {
    { "BubbleColorI", &Global::settings.chat_bubble_color_i},
    { "BubbleColorO", &Global::settings.chat_bubble_color_o }
  };

  settings_qstring_hash = {
    { "usrKey", &Global::settings.profile_key_str },
    { "usrName", &Global::settings.profile_name_str },
    { "avatarPath", &Global::settings.profile_avatar_str }
  };

  settings_bool_hash = {
    { "updateNotification", &Global::settings.notification.update_notification },
    { "messageNotification", &Global::settings.notification.message_notification },
    { "messageDetailNotification", &Global::settings.notification.message_detail_notification },
    { "autoUpdate", &Global::settings.update.auto_update },
    { "autoCheckUpdate", &Global::settings.update.auto_check_update }
  };

  //! defaults
  Global::settings.chat_bubble_color_i = Global::color_defaultChatBubbleI;
  Global::settings.chat_bubble_color_o = Global::color_defaultChatBubbleO;
  Global::settings.notification.message_detail_notification = true;
  Global::settings.notification.message_notification = true;
  Global::settings.notification.update_notification = true;
  Global::settings.update.auto_check_update = true;
  Global::settings.update.auto_update = true;

}

void AppDataManager::loadSettings()
{
  Parsley::File file(Global::settings_file_dir, loop);
  if(!file.open(O_RDWR | O_CREAT, 0755, Parsley::SyncMode))
    {
      return;
    }
  std::string data = file.readAll();
  QJsonParseError jsonError;
  QJsonDocument doc = QJsonDocument::fromJson(QByteArray(data.data(), data.size()), &jsonError);
  if(jsonError.error == QJsonParseError::NoError
     && doc.isObject())
    {
      QJsonObject settingsJson = doc.object();

      for (std::pair<QString, int*> element : settings_int_hash)
        *element.second = settingsJson[element.first].toInt();

      for (std::pair<QString, QColor*> element : settings_qcolor_hash)
        *element.second = QColor(settingsJson[element.first].toString());

      for (std::pair<QString, QString*> element : settings_qstring_hash)
        *element.second = settingsJson[element.first].toString();

      for (std::pair<QString, bool*> element : settings_bool_hash)
        *element.second = settingsJson[element.first].toBool();
    }
  else
    {
      std::string writeData = makeDefaultSettings().toJson(QJsonDocument::Indented).toStdString();
      file.write(writeData, Parsley::SyncMode);
      Log::dat(Log::Info, "AppDataManager::readSettings()", "Settings file first created:");
      Log::dat(Log::Info, "AppDataManager::readSettings()", "\n"+QString::fromStdString(writeData));
    }

  file.close(Parsley::SyncMode);
}

void AppDataManager::loadUsrList()
{
  Parsley::File file(Global::contacts_file_dir, loop);
  if(!file.open(O_RDWR | O_CREAT, 0755, Parsley::SyncMode))
    {
      return;
    }
  std::string data = file.readAll();
  QJsonParseError jsonErr;
  QJsonDocument doc = QJsonDocument::fromJson(QByteArray(data.data(), data.size()), &jsonErr);
  if(jsonErr.error == QJsonParseError::NoError)
    {
      if(doc.isObject())
        {
          QJsonObject usrListObj = doc.object();
          QStringList uuidList = usrListObj.keys();  //get usr_key as a string list

          for(int i = 0; i < uuidList.count(); i++)
            {
              QString *tempUuidStr = &uuidList[i];
              QJsonObject tempUsrProfileObj = usrListObj[*tempUuidStr].toObject();

              UsrProfile usrProfileStruct;
              usrProfileStruct.key = tempUsrProfileObj["usrKey"].toString();
              usrProfileStruct.name = tempUsrProfileObj["usrName"].toString();
              usrProfileStruct.avatar = tempUsrProfileObj["avatarPath"].toString();
              usrProfileStruct.online = false;

              UsrData *usrData = new UsrData(&Global::settings.profile_key_str, usrProfileStruct, this);
              usr_data_hash.insert(*tempUuidStr, usrData);

              Global::TEST_printUsrProfileStruct(*usrData->getUsrProfileStruct(),"adding from disk");
            }
        }
    }
  else
    {
      std::string data = "";
      file.write(data, Parsley::SyncMode);
      Log::dat(Log::Critical
               , "AppDataManager::loadUsrList()"
               , "Contact list file broken, broken file is cleared");
      return;
    }

  file.close(Parsley::SyncMode);
}

void AppDataManager::writeSettings()
{
  Parsley::File file(Global::settings_file_dir, loop);
  if(!file.open(O_RDWR | O_CREAT, 0755, Parsley::SyncMode))
    {
      return;
    }

  QJsonObject settingsObj;
  for (std::pair<QString, int*> element : settings_int_hash)
    settingsObj.insert(element.first, *element.second);

  for (std::pair<QString, QColor*> element : settings_qcolor_hash)
    settingsObj.insert(element.first, element.second->name());

  for (std::pair<QString, QString*> element : settings_qstring_hash)
    settingsObj.insert(element.first, *element.second);

  for (std::pair<QString, bool*> element : settings_bool_hash)
    settingsObj.insert(element.first, *element.second);

  QJsonDocument outJsonDoc;
  outJsonDoc.setObject(settingsObj);

  std::string outData = outJsonDoc.toJson().toStdString();
  file.write(outData, Parsley::SyncMode);
  file.close(Parsley::SyncMode);

  Log::dat(Log::Info
           , "AppDataManager::writeCurrentConfig()"
           , "Config file updated.");
}

void AppDataManager::loadUpdates()
{
  Parsley::File file(Global::update_file_dir, loop);
  if(!file.open(O_RDWR | O_CREAT, 0755, Parsley::SyncMode))
    {
      return;
    }
  std::string data = file.readAll();
  QJsonParseError jsonError;
  QJsonDocument doc = QJsonDocument::fromJson(QByteArray(data.data(), data.size()), &jsonError);
  if(jsonError.error == QJsonParseError::NoError)
    {
      if(doc.isObject())
        {
          QJsonObject readJsonObj = doc.object();

          int readVersion[3] = {
            readJsonObj.value("stable_version").toInt(),
            readJsonObj.value("beta_version").toInt(),
            readJsonObj.value("alpha_version").toInt()
          };

          if(Global::versionCompare(Global::current_version, readVersion))
            {
              for(int i = 0; i < 3; i ++)
                {
                  Global::update_struct.version[i] = readVersion[i];
                }
              emit updatesAvailable();
            }
        }
    }

  file.close(Parsley::SyncMode);
}





