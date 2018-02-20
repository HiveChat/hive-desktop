#include "AppDataManager.h"

std::forward_list<AppDataManager::NetBuffer*> AppDataManager::inbound_net_buffer;
std::mutex AppDataManager::inbound_net_buffer_mutex;
std::forward_list<AppDataManager::NetBuffer*> AppDataManager::outbound_net_buffer;
std::mutex AppDataManager::outbound_net_buffer_mutex;


AppDataManager::AppDataManager(QObject *parent) : QObject(parent)
{
  initVariable();
  checkFiles();
  readSettings();
  loadUsrList();
  loadFonts();
  loadTimerTasks();
}

/////////////thread
AppDataManager::~AppDataManager()
{
  Log::gui(Log::Normal, "AppDataManager::~AppDataManager()", "Successfully destroyed AppDataManager...");
}

bool AppDataManager::pushInboundBuffer(NetBuffer *buffer)
{
  std::lock_guard<std::mutex> guard(inbound_net_buffer_mutex);
  inbound_net_buffer.push_front(buffer);
}

bool AppDataManager::pushOutboundBuffer(NetBuffer *buffer)
{
  std::lock_guard<std::mutex> guard(outbound_net_buffer_mutex);
  outbound_net_buffer.push_front(buffer);
}

void AppDataManager::checkSettings()
{
  if(Global::settings.modified_lock)
    {
      Log::dat(Log::Normal, "AppDataManager::checkSettings()", "Settings changed.");
      writeSettings();
      Global::settings.modified_lock = false;
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


///////////!thread

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

void AppDataManager::onUsrEntered(const UsrProfileStruct &usrProfileStruct) // logic problem here? too complicated?
{
  if(Global::online_usr_data_hash.contains(usrProfileStruct.key))
    {
      Log::dat(Log::Normal, "DataManager::onUsrEntered()", "incoming user already exist in online list");
      UsrData *usrData = Global::online_usr_data_hash.value(usrProfileStruct.key);
      if(usrProfileStruct != *usrData->getUsrProfileStruct())
        {
          usrData->setUsrProfileStruct(usrProfileStruct);
          emit usrProfileChanged(usrData);
          Log::dat(Log::Normal, "DataManager::onUsrEntered()", "user profile changed");
        }
    }
  else if(Global::offline_usr_data_hash.contains(usrProfileStruct.key))
    {
      Log::dat(Log::Normal, "DataManager::onUsrEntered()", "incoming user already exist in offline list");
      Global::online_usr_data_hash.insert(usrProfileStruct.key, Global::offline_usr_data_hash.value(usrProfileStruct.key));
      UsrData *usrData = Global::online_usr_data_hash.value(usrProfileStruct.key);
      if(usrProfileStruct != *usrData->getUsrProfileStruct())
        {
          usrData->setUsrProfileStruct(usrProfileStruct);
          updateUsr(usrProfileStruct);
          emit usrProfileChanged(usrData);
          Log::dat(Log::Normal, "DataManager::onUsrEntered()", "user profile changed");
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

void AppDataManager::checkFiles()
{
  checkDir(Global::data_location_dir);
  checkDir(Global::user_data_dir);
  checkDir(Global::log_dir);
}

bool AppDataManager::checkDir(const QString &directory)
{
  QDir dir(directory);
  if(!dir.exists())
    {
      //log here
      if(!dir.mkdir(directory))
        {
          //log here
          return false;
        }
    }
  return true;
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

  Log::dat(Log::Normal
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

void AppDataManager::loadTimerTasks()
{
  QTimer *checkSettingsTimer = new QTimer(this);
  connect(checkSettingsTimer, &QTimer::timeout,
          [this]() {
            checkSettings();
          });
  checkSettingsTimer->setSingleShot(false);
  checkSettingsTimer->setInterval(1000);
  checkSettingsTimer->start();
}



