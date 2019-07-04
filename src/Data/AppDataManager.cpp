#include "AppDataManager.h"

DoubleBuffer<NetPacket*> AppDataManager::net_buffer_in;
DoubleBuffer<NetPacket*> AppDataManager::net_buffer_out;
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
  net_buffer_in.push(packet);
}

void AppDataManager::pushOutboundBuffer(NetPacket *packet)
{
  net_buffer_out.push(packet);
}

bool AppDataManager::isUsrNew(const QString &uuid)
{
  return !usr_data_hash.contains(uuid);
}

void AppDataManager::checkSettings(Agio::Timer *)
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

void AppDataManager::updateUsr(const UsrProfile &p)
{
  QString uuid = p.key;
  QString ipAddr = p.ip;
  QString usrName = p.name;
  QString avatarPath = p.avatar;

  Agio::File f(Global::contacts_file_dir, loop);
  if(!f.open(O_RDWR | O_CREAT, 0755, Agio::Sync))
    {
      return;
    }
  std::string data = f.readAll();
  QJsonParseError jsonErr;
  QJsonDocument inJsonDoc = QJsonDocument::fromJson(QByteArray(data.data(), data.size()), &jsonErr);
  if(jsonErr.error == QJsonParseError::NoError)
    {
      if(inJsonDoc.isObject())
        {
          QJsonObject usrListObj = inJsonDoc.object();
          QJsonObject usrInfoObj;
          usrInfoObj.insert("usrKey", uuid);
          usrInfoObj.insert("usrName", usrName);
          usrInfoObj.insert("avatarPath", avatarPath);
          if(usrListObj.contains(uuid))
            {
              usrListObj.remove(uuid);
            }
          usrListObj.insert(uuid, usrInfoObj);

          QJsonDocument outJsonDoc;
          outJsonDoc.setObject(usrListObj);
          std::string data = outJsonDoc.toJson().toStdString();
          f.truncate(0, Agio::Sync);
          f.write(data, Agio::Sync);
        }
    }
  else //! TODO: put all loaded contacts in!!
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
      f.truncate(0, Agio::Sync);
      f.write(data, Agio::Sync);
    }

  f.close(Agio::Sync);
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
void AppDataManager::onUsrEntered(UsrProfile &profile) // logic problem here? too complicated?
{
  if(isUsrNew(profile.key))
    {
      Log::dat(Log::Info, "DataManager::onUsrEntered()", "New user");
      profile.online = true;
      UsrData *data = new UsrData(&Global::settings.profile_uuid_str, profile);
      usr_data_hash.insert(profile.key, data);
      updateUsr(profile);
      emit usrProfileLoaded(data);
    }
  else
    {
      UsrData *data = usr_data_hash.value(profile.key);
      qDebug()<<data->getKey();
      Global::TEST_printUsrProfile(*data->getProfile(), "000000000000");
      Global::TEST_printUsrProfile(profile, "111111111111");
      if(profile != *data->getProfile())
        {
          data->setUsrProfile(profile);
          emit usrProfileChanged(data);
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

void AppDataManager::onMessageCome(const Message::TextMessage &m, bool fromMe)
{
  if(fromMe)
    {
      qDebug()<<"fromme";
      usr_data_hash.value(m.reciever)->addUnreadMessage(m);
    }
  else
    {
      qDebug()<<"notfromme";
      usr_data_hash.value(m.sender)->addUnreadMessage(m);
    }
  emit messageLoaded(m, fromMe);
}

void AppDataManager::onUpdateAvailable()
{
  if(Global::update_struct.version[0] == 0
     && Global::update_struct.version[1] == 0
     && Global::update_struct.version[2] == 0)
    {
      return;
    }

  int outVersion[3];
  memcpy(&outVersion, &Global::current_version, sizeof(Global::current_version));

  Agio::File file(Global::update_file_dir, loop);
  if(!file.open(O_RDWR | O_CREAT, 0755, Agio::Sync))
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
              file.close(Agio::Sync);
              emit updateAvailable();

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
  file.truncate(0, Agio::Sync);
  file.write(outData, Agio::Sync);
  file.close(Agio::Sync);

  emit updateAvailable();
}

void AppDataManager::run()
{
  initVariable();

  loop = new Agio::Loop();
  Agio::on(&net_buffer_in.onPushed, this, &AppDataManager::wakeLoop);

  read_inbound_async = new Agio::AsyncEvent(loop);
  Agio::on(&read_inbound_async->onCalled, this, &AppDataManager::readInboundNetBuffer);

  touchDir(Global::data_location_dir);
  touchDir(Global::user_data_dir);
  touchDir(Global::log_dir);
  touchFile(Global::settings_file_dir);

  loadSettings();
  loadUsrList();

  Agio::Timer checkSettingsTimer(loop);
  Agio::on(&checkSettingsTimer.onTimedOut, this, &AppDataManager::checkSettings);
  checkSettingsTimer.start(2000, 1000);

  loop->run(UV_RUN_DEFAULT);
}

void AppDataManager::readInboundNetBuffer()
{
  inbound_net_buffer_reading = true; // not 100% safe
  NetPacket *packet = net_buffer_in.front();
  Log::net(Log::Info, "AppDataManager::readInboundNetBuffer()","Checking Package");

  while (packet)
    {
      //! See if JSON object is complete.
      QJsonParseError err;
      QJsonDocument doc = QJsonDocument::fromJson(QByteArray::fromStdString(packet->data), &err);
      QString ipAddr = QString::fromStdString(packet->ip_addr);
      //! HiveDoubleBuffer calls std::list::pop_front(), which automatically calls destructor of NetPacket *p.
      net_buffer_in.pop();
      if(err.error != QJsonParseError::NoError || !doc.isObject())
        {
          Log::net(Log::Warning, "AppDataManager::readInboundNetBuffer(): failed to parse JSON\n", packet->data.c_str());
          Log::net(Log::Warning, "AppDataManager::readInboundNetBuffer()", err.errorString());
          packet = net_buffer_in.front();
          continue;
        }

      //! See if the package is for me.
      QJsonObject packetJson = doc.object();
      QString receiverKey = packetJson.value("receiver").toString();
      if(receiverKey != Global::settings.profile_uuid_str
         && receiverKey != BROADCAST_UUID)
        {
          Log::net(Log::Warning
                   , "AppDataManager::readInboundNetBuffer()"
                   , "Package wrong destination: " + receiverKey + " My Id: " + Global::settings.profile_uuid_str);
          packet = net_buffer_in.front();
          continue;
        }

      //! Start processing message
      MessageType messageType = (MessageType) packetJson.value("msgType").toInt();
      switch (messageType) {
        case MessageType::HeartBeat:
          {
            UsrProfile profile;
            profile.ip = ipAddr;
            profile.key = packetJson.value("sender").toString();
            profile.name = packetJson.value("name").toString();
            profile.avatar = packetJson.value("avatar").toString();
            profile.online = true;
            onUsrEntered(profile);
            break;
          }
        case MessageType::TextMessage:
          {
            Message::TextMessage message;
            message.index = packetJson.value("index").toInt();
            message.time = packetJson.value("time").toInt();
            message.reciever = packetJson.value("receiver").toString();
            message.sender = packetJson.value("sender").toString();
            message.message = packetJson.value("message").toString();

            onMessageCome(message, message.sender == Global::settings.profile_uuid_str);
//            processTextMessage();
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
      packet = net_buffer_in.front();
    }
  inbound_net_buffer_reading = false;
}

void AppDataManager::wakeLoop(DoubleBuffer<NetPacket *> *buf)
{
  if(!inbound_net_buffer_reading)
    read_inbound_async->send();
}

bool AppDataManager::touchFile(const std::string &path)
{
  Agio::File f(path, loop);
  int r = f.open(O_WRONLY | O_CREAT, 0664, Agio::Sync);
  f.close(Agio::Sync);
  return r;
}

bool AppDataManager::touchDir(const std::string &dir)
{
  return Agio::File::mkdir(dir, 0755, loop, Agio::Sync) == 0;
}

QJsonDocument AppDataManager::makeDefaultSettings()
{
  Global::settings.profile_uuid_str = makeUuid();
  Global::settings.profile_avatar_str = ":/avatar/avatar/default.png";
  Global::settings.profile_name_str = QHostInfo::localHostName();


  QJsonObject obj;
  obj.insert("usrKey", Global::settings.profile_uuid_str);
  obj.insert("usrName", Global::settings.profile_name_str);
  obj.insert("avatarPath", Global::settings.profile_avatar_str);
  obj.insert("BubbleColorI", Global::color_defaultChatBubbleI.name());
  obj.insert("BubbleColorO", Global::color_defaultChatBubbleO.name());

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
    { "usrKey", &Global::settings.profile_uuid_str },
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
  Agio::File file(Global::settings_file_dir, loop);
  if(!file.open(O_RDWR | O_CREAT, 0755, Agio::Sync))
    {
      return;
    }
  std::string data = file.readAll();
  qDebug()<< "settings from disk:"<<data.c_str();
  QJsonParseError jsonErr;
  QJsonDocument doc = QJsonDocument::fromJson(QByteArray(data.data(), data.size()), &jsonErr);
  if(jsonErr.error == QJsonParseError::NoError
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
      Log::dat(Log::Info, "AppDataManager::readSettings()", "Json parse error:" + jsonErr.errorString());
      std::string writeData = makeDefaultSettings().toJson(QJsonDocument::Indented).toStdString();
      file.truncate(0, Agio::Sync);
      file.write(writeData, Agio::Sync);
      Log::dat(Log::Info, "AppDataManager::readSettings()", "Settings file first created:\n" + QString::fromStdString(writeData));
    }

  file.close(Agio::Sync);
}

void AppDataManager::loadUsrList()
{
  Agio::File file(Global::contacts_file_dir, loop);
  if(!file.open(O_RDWR | O_CREAT, 0755, Agio::Sync))
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

              UsrProfile p;
              p.key = tempUsrProfileObj["usrKey"].toString();
              p.name = tempUsrProfileObj["usrName"].toString();
              p.avatar = tempUsrProfileObj["avatarPath"].toString();
              p.online = false;

              UsrData *usrData = new UsrData(&Global::settings.profile_uuid_str, p);
              usr_data_hash.insert(*tempUuidStr, usrData);

              Global::TEST_printUsrProfile(*usrData->getProfile(),"adding from disk");
            }
        }
    }
  else
    {
      file.truncate(0, Agio::Sync);
      file.write("", Agio::Sync);
      Log::dat(Log::Critical
               , "AppDataManager::loadUsrList()"
               , "Contact list file broken, broken file is cleared");
      return;
    }

  file.close(Agio::Sync);
}

void AppDataManager::writeSettings()
{
  Agio::File file(Global::settings_file_dir, loop);
  if(!file.open(O_RDWR | O_CREAT, 0755, Agio::Sync))
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
  file.truncate(0, Agio::Sync);
  file.write(outData, Agio::Sync);
  file.close(Agio::Sync);

  Log::dat(Log::Info
           , "AppDataManager::writeCurrentConfig()"
           , "Config file updated.");
}

void AppDataManager::loadUpdates()
{
  Agio::File file(Global::update_file_dir, loop);
  if(!file.open(O_RDWR | O_CREAT, 0755, Agio::Sync))
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
              emit updateAvailable();
            }
        }
    }

  file.close(Agio::Sync);
}





