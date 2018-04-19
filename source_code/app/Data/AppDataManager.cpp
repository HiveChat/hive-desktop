#include "AppDataManager.h"

HiveDoubleBuffer<NetPacket*> AppDataManager::inboundNetBuffer;
HiveDoubleBuffer<NetPacket*> AppDataManager::outboundNetBuffer;

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

bool AppDataManager::pushInboundBuffer(NetPacket *packet)
{
  inboundNetBuffer.push_front(packet);
}

bool AppDataManager::pushOutboundBuffer(NetPacket *packet)
{
  outboundNetBuffer.push_front(packet);
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

void AppDataManager::updateUsr(const UsrProfileStruct &usrProfileStruct)
{
  QString uuid = usrProfileStruct.key;
  QString ipAddr = usrProfileStruct.ip;
  QString usrName = usrProfileStruct.name;
  QString avatarPath = usrProfileStruct.avatar;

  QFile f(Global::contacts_file_dir);
  if(!f.open(QIODevice::ReadWrite | QIODevice::Text))
    {
      return;
    }

  QTextStream out(&f);
  QTextStream in(&f);
  QByteArray inByteArray = in.readAll().toUtf8();

  QJsonParseError jsonError;
  QJsonDocument inJsonDoc = QJsonDocument::fromJson(inByteArray, &jsonError);
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

              f.resize(0);
              out<<outJsonDoc.toJson()<<endl;
            }
          else
            {
              if(usrListObj[uuid] != usrInfoObj)
                {
                  usrListObj.remove(uuid);
                  usrListObj.insert(uuid, usrInfoObj);

                  QJsonDocument outJsonDoc;
                  outJsonDoc.setObject(usrListObj);

                  f.resize(0);
                  out<<outJsonDoc.toJson()<<endl;
                }
            }
        }
    }
  else
    {
      qDebug()<<"else";
      QJsonObject usrInfoObj;
      usrInfoObj.insert("usrKey", uuid);
      usrInfoObj.insert("usrName", usrName);
      usrInfoObj.insert("avatarPath", avatarPath);

      QJsonObject usrListObj;
      usrListObj.insert(uuid, usrInfoObj);

      QJsonDocument outJsonDoc;
      outJsonDoc.setObject(usrListObj);

      f.resize(0);
      out<<outJsonDoc.toJson(QJsonDocument::Indented);  ///QJsonDocument::Compact
    }

  f.flush();
  f.close();

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
void AppDataManager::onUsrEntered(const UsrProfileStruct &usrProfileStruct) // logic problem here? too complicated?
{
  if(Global::online_usr_data_hash.contains(usrProfileStruct.key))
    {
      Log::dat(Log::Info, "DataManager::onUsrEntered()", "incoming user already exist in online list");
      UsrData *usrData = Global::online_usr_data_hash.value(usrProfileStruct.key);
      if(usrProfileStruct != *usrData->getUsrProfileStruct())
        {
          usrData->setUsrProfileStruct(usrProfileStruct);
          emit usrProfileChanged(usrData);
          Log::dat(Log::Info, "DataManager::onUsrEntered()", "user profile changed");
        }
    }
  else if(Global::offline_usr_data_hash.contains(usrProfileStruct.key))
    {
      Log::dat(Log::Info, "DataManager::onUsrEntered()", "incoming user already exist in offline list");
      Global::online_usr_data_hash.insert(usrProfileStruct.key, Global::offline_usr_data_hash.value(usrProfileStruct.key));
      UsrData *usrData = Global::online_usr_data_hash.value(usrProfileStruct.key);
      if(usrProfileStruct != *usrData->getUsrProfileStruct())
        {
          usrData->setUsrProfileStruct(usrProfileStruct);
          updateUsr(usrProfileStruct);
          emit usrProfileChanged(usrData);
          Log::dat(Log::Info, "DataManager::onUsrEntered()", "user profile changed");
        }
    }
  else
    {
      UsrData *userData = new UsrData(&Global::settings.profile_key_str, usrProfileStruct, this);
      Global::online_usr_data_hash.insert(usrProfileStruct.key, userData);
      updateUsr(usrProfileStruct);
      emit usrProfileLoaded(userData);
      qDebug()<<"@DataManager::onUsrEntered: User profile Created.";

    }

  return;
}

void AppDataManager::onUsrLeft(QString *usrKey)
{

}

void AppDataManager::onMessageCome(const Message::TextMessage &messageStruct, bool fromMe)
{
  if(fromMe)
    {
      qDebug()<<"fromme";
      Global::online_usr_data_hash.value(messageStruct.reciever)->addUnreadMessage(messageStruct);
    }
  else
    {
      qDebug()<<"notfromme";
      Global::online_usr_data_hash.value(messageStruct.sender)->addUnreadMessage(messageStruct);
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

  QFile file(Global::update_file_dir);
  if(!file.open(QIODevice::ReadWrite | QIODevice::Text))
    {
      return;
    }

  QTextStream in(&file);
  QTextStream out(&file);
  QByteArray inByteArray = in.readAll().toUtf8();
  int outVersion[3];
  memcpy(&outVersion, &Global::current_version, sizeof(Global::current_version));

  if(!inByteArray.isEmpty())
    {
      QJsonParseError jsonError;
      QJsonDocument inJsonDoc = QJsonDocument::fromJson(inByteArray, &jsonError);
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
                  file.close();
                  file.flush();
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
    }

  file.resize(0);

  out << makeUpdateJson(outVersion).toJson(QJsonDocument::Indented) << endl;

  file.close();
  file.flush();

  emit updatesAvailable();
}

void AppDataManager::run()
{
  initVariable();

  loop = new Parsley::Loop();

  inboundNetBuffer.bindCb(std::bind(&AppDataManager::wakeLoop, this, std::placeholders::_1));

  read_inbound_async = new Parsley::Async(loop);
  read_inbound_async->bindCb(std::bind(&AppDataManager::readInboundNetBuffer, this));

  touchDir(Global::data_location_dir.toUtf8().data());
  touchDir(Global::user_data_dir.toUtf8().data());
  touchDir(Global::log_dir.toUtf8().data());

  Parsley::File file(loop);
  file.open(QByteArray(Global::settings_file_dir.toUtf8()).data(), O_RDWR | O_CREAT, 0755, Parsley::SyncMode);
  file.close();

  Parsley::File file2(loop);
  file2.open("/Users/echo/a.txt", O_RDWR | O_CREAT, 0755, Parsley::SyncMode);
  std::string str = "tim is here i don't know where";
//  file2.writeAll(str, Parsley::SyncMode);
  file2.close();

  readSettings();
  loadUsrList();
  loadFonts();

  Parsley::Timer checkSettingsTimer(loop);
  checkSettingsTimer.bindCb(std::bind(&AppDataManager::checkSettings, this));
  checkSettingsTimer.start(2000, 1000);

  loop->run(UV_RUN_DEFAULT);
}

void AppDataManager::readInboundNetBuffer()
{
  NetPacket *p = inboundNetBuffer.front();

  while (p)
    {
      //! See if JSON object is complete.
      QJsonParseError err;
      QJsonDocument doc = QJsonDocument::fromJson(QByteArray(p->data, p->len), &err);
      QString ipAddr = QByteArray(p->ipAddr, 17);
      //! HiveDoubleBuffer calls std::list::pop_front()
      //! which automatically calls destructor of NetPacket *p.
      inboundNetBuffer.pop_front();
      if(err.error != QJsonParseError::NoError || !doc.isObject())
        {
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
            UsrProfileStruct usr_profile;
//            usr_profile.ip = addr;
            usr_profile.key = packetJson.value("sender").toString();
            usr_profile.name = packetJson.value("name").toString();
            usr_profile.avatar = packetJson.value("avatar").toString();
            onUsrEntered(usr_profile);
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
}

void AppDataManager::wakeLoop(HiveDoubleBuffer<NetPacket *> *buf)
{
  if(!inboundNetBufferReading)
    read_inbound_async->send();
}

bool AppDataManager::touchFile(char* path)
{
  Parsley::File f(loop);
  int ret = f.open(path, O_WRONLY | O_CREAT, 0644, Parsley::SyncMode);
  f.close(Parsley::AsyncMode);
  return ret;
}

bool AppDataManager::touchDir(char *dir)
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

void AppDataManager::readSettings()
{
  QFile file(Global::settings_file_dir);
  if(!file.open(QIODevice::ReadWrite | QIODevice::Text))
    {
      return;
    }
  QTextStream in(&file);
  QTextStream out(&file);

  QByteArray inByteArray = in.readAll().toUtf8();
  QJsonParseError jsonError;
  QJsonDocument inDoc = QJsonDocument::fromJson(inByteArray, &jsonError);
  if(jsonError.error == QJsonParseError::NoError
     && inDoc.isObject())
    {
      QJsonObject settingsJson = inDoc.object();

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
      file.resize(0);
      out<<makeDefaultSettings().toJson(QJsonDocument::Indented)<<endl;
    }

  file.flush();
  file.close();
}

void AppDataManager::loadUsrList()
{
  QFile file(Global::contacts_file_dir);
  if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
      return;
    }
  QTextStream in(&file);
  QByteArray inByteArray = in.readAll().toUtf8();

  ///JSon
  QJsonParseError jsonError;
  QJsonDocument inJsonDoc = QJsonDocument::fromJson(inByteArray, &jsonError);
  if(jsonError.error == QJsonParseError::NoError)
    {
      if(inJsonDoc.isObject())
        {
          QJsonObject usrListObj = inJsonDoc.object();
          QStringList uuidList = usrListObj.keys();  //get usr_key as a string list

          for(int i = 0; i < uuidList.count(); i++)
            {
              QString *tempUsrKeyStr = &uuidList[i];
              QJsonObject tempUsrProfileObj = usrListObj[*tempUsrKeyStr].toObject();

              UsrProfileStruct usrProfileStruct;
              usrProfileStruct.key = tempUsrProfileObj["usrKey"].toString();
              usrProfileStruct.name = tempUsrProfileObj["usrName"].toString();
              usrProfileStruct.avatar = tempUsrProfileObj["avatarPath"].toString();

              UsrData *usrData = new UsrData(&Global::settings.profile_key_str, usrProfileStruct, this);
              Global::offline_usr_data_hash.insert(*tempUsrKeyStr, usrData);
            }
        }
    }
  else
    {
      file.resize(0);
      Log::dat(Log::Critical
               , "AppDataManager::loadUsrList()"
               , "Contact list file broken, broken file is cleared");
      return;
    }

  file.flush();
  file.close();
}

void AppDataManager::writeSettings()
{
  QFile file(Global::settings_file_dir);
  if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
      return;
    }
  QTextStream out(&file);

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
  file.resize(0);
  out << outJsonDoc.toJson();
  file.flush();
  file.close();

  Log::dat(Log::Info
           , "AppDataManager::writeCurrentConfig()"
           , "Config file updated.");
}

void AppDataManager::loadFonts()
{

#ifdef Q_OS_WIN
    QString font_family = "Verdana";
    GlobalData::font_chatTextEditor = QFont(font_family, 11);
    GlobalData::font_main = QFont(font_family, 6);
    GlobalData::font_chatBubble = GlobalData::font_main;
    GlobalData::font_chatBubble.setPointSize(10);
    GlobalData::font_combWidgetUsrName = GlobalData::font_main;
    GlobalData::font_combWidgetUsrName.setPointSize(10);
    GlobalData::font_combWidgetIpAddr = GlobalData::font_main;
    GlobalData::font_combWidgetIpAddr.setPointSize(7);
    GlobalData::font_menuButton = GlobalData::font_main;
    GlobalData::font_menuButton.setPointSize(10);
    GlobalData::font_scrollStackTitle = GlobalData::font_main;
    GlobalData::font_scrollStackTitle.setPointSize(10);
    GlobalData::font_scrollStackSubtitle = GlobalData::font_main;
    GlobalData::font_scrollStackSubtitle.setPointSize(9);
#endif //Q_OS_WIN


#ifndef Q_OS_WIN ///windows can't load font from qrc, don't know why.
  int fontId;
  QString fontFamily;

  fontId = QFontDatabase::addApplicationFont(":/font/font/GillSans.ttc");
  if(fontId == -1)
    {
      return;
    }

  fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);

  Global::font_chatTextEditor = QFont(fontFamily, 16);
  if(fontId == -1)
    {
      return;
    }

  fontId = QFontDatabase::addApplicationFont(":/font/font/Futura.ttc");
  fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
  Global::font_main = QFont(fontFamily);
  Global::font_chatBubble = Global::font_main;
  Global::font_chatBubble.setPointSize(14);
  Global::font_combWidgetUsrName = Global::font_main;
  Global::font_combWidgetUsrName.setPointSize(15);
  Global::font_combWidgetIpAddr = Global::font_main;
  Global::font_combWidgetIpAddr.setPointSize(11);
  Global::font_menuButton = Global::font_main;
  Global::font_menuButton.setPointSize(14);
  Global::font_scrollStackTitle = Global::font_main;
  Global::font_scrollStackTitle.setPointSize(15);
  Global::font_scrollStackSubtitle = Global::font_main;
  Global::font_scrollStackSubtitle.setPointSize(13);

#endif //Q_OS_WIN

}

void AppDataManager::loadUpdates()
{
  QFile file(Global::update_file_dir);
  if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
      return;
    }

  QTextStream in(&file);
  QByteArray inByteArray = in.readAll().toUtf8();

  if(!inByteArray.isEmpty())
    {
      QJsonParseError jsonError;
      QJsonDocument inJsonDoc = QJsonDocument::fromJson(inByteArray, &jsonError);
      if(jsonError.error == QJsonParseError::NoError)
        {
          if(inJsonDoc.isObject())
            {
              QJsonObject readJsonObj = inJsonDoc.object();

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
    }

  file.close();
  file.flush();
}





