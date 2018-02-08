#include "AppDataManager.h"

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

void AppDataManager::checkSettings()
{
  if(GlobalData::settings_struct.modified_lock)
    {
      Log::dat(Log::Normal, "AppDataManager::checkSettings()", "Settings changed.");
      writeSettings();
      GlobalData::settings_struct.modified_lock = false;
    }
}

QJsonDocument AppDataManager::makeUpdateJson(const int stable[])
{
  QJsonObject write_json_obj;
  write_json_obj.insert("stable_version", QJsonValue(stable[0]));
  write_json_obj.insert("beta_version", QJsonValue(stable[1]));
  write_json_obj.insert("alpha_version", QJsonValue(stable[2]));

  QJsonDocument write_json_document;
  write_json_document.setObject(write_json_obj);
  return write_json_document;
}


///////////!thread

void AppDataManager::updateUsr(const UsrProfileStruct &usrProfileStruct)
{
  QString usrKey = usrProfileStruct.key;
  QString ipAddr = usrProfileStruct.ip;
  QString usrName = usrProfileStruct.name;
  QString avatarPath = usrProfileStruct.avatar;

  QFile file(GlobalData::contacts_file_dir);
  if(!file.open(QIODevice::ReadWrite | QIODevice::Text))
    {
      return;
    }

  QTextStream out(&file);
  QTextStream in(&file);
  QByteArray inByteArray = in.readAll().toUtf8();

  QJsonParseError jsonError;
  QJsonDocument readJsonDocument = QJsonDocument::fromJson(inByteArray, &jsonError);
  if(jsonError.error == QJsonParseError::NoError)
    {
      if(readJsonDocument.isObject())
        {
          QJsonObject usrListJsonObj = readJsonDocument.object();
          QJsonObject usrInfoJsonObj;
          usrInfoJsonObj.insert("usrKey", usrKey);
          usrInfoJsonObj.insert("usrName", usrName);
          usrInfoJsonObj.insert("avatarPath", avatarPath);
          if(!usrListJsonObj.contains(usrKey))
            {
              usrListJsonObj.insert(usrKey, usrInfoJsonObj);

              QJsonDocument writeJsonDocument;
              writeJsonDocument.setObject(usrListJsonObj);

              file.resize(0);
              out<<writeJsonDocument.toJson()<<endl;
            }
          else
            {
              if(usrListJsonObj[usrKey] != usrInfoJsonObj)
                {
                  usrListJsonObj.remove(usrKey);
                  usrListJsonObj.insert(usrKey, usrInfoJsonObj);

                  QJsonDocument writeJsonDocument;
                  writeJsonDocument.setObject(usrListJsonObj);

                  file.resize(0);
                  out<<writeJsonDocument.toJson()<<endl;
                }
            }
        }
    }
  else
    {
      qDebug()<<"else";
      QJsonObject usr_info_json_obj;
      usr_info_json_obj.insert("usrKey", usrKey);
      usr_info_json_obj.insert("usrName", usrName);
      usr_info_json_obj.insert("avatarPath", avatarPath);

      QJsonObject usr_list_json_obj;
      usr_list_json_obj.insert(usrKey, usr_info_json_obj);

      QJsonDocument write_json_document;
      write_json_document.setObject(usr_list_json_obj);

      file.resize(0);
      out<<write_json_document.toJson(QJsonDocument::Indented);  ///QJsonDocument::Compact
    }

  file.flush();
  file.close();

}

void AppDataManager::deleteUsr(const QStringList usrInfoStrList)
{
  QFile file(GlobalData::contacts_file_dir);
  if(!file.open(QIODevice::ReadWrite | QIODevice::Text))
  {
    return;
  }

  QTextStream in(&file);
  QTextStream out(&file);

  QByteArray in_byte_array = in.readAll().toUtf8();

  ///JSon
  QJsonParseError json_error;
  QJsonDocument readJsonDocument = QJsonDocument::fromJson(in_byte_array, &json_error);
  if(json_error.error == QJsonParseError::NoError)
    {
      if(readJsonDocument.isObject())
        {
          QJsonObject usrListJsonObj = readJsonDocument.object();
          usrListJsonObj.erase(usrListJsonObj.find(usrInfoStrList.at(0)));

          QJsonDocument writeJsonDocument;
          writeJsonDocument.setObject(usrListJsonObj);
          file.resize(0);
          out<<writeJsonDocument.toJson(QJsonDocument::Indented)<<endl;

        }
    }
  else
    {
      qDebug()<<"Contact delete failed, is file empty?";

    }

  file.close();
  file.flush();
}

void AppDataManager::onUsrEntered(const UsrProfileStruct &usrProfileStruct) // logic problem here? too complicated?
{
  if(GlobalData::online_usr_data_hash.contains(usrProfileStruct.key))
    {
      Log::dat(Log::Normal, "DataManager::onUsrEntered()", "incoming user already exist in online list");
      UsrData *recordedUsrData = GlobalData::online_usr_data_hash.value(usrProfileStruct.key);
      if(usrProfileStruct != *recordedUsrData->getUsrProfileStruct())
        {
          recordedUsrData->setUsrProfileStruct(usrProfileStruct);
          emit usrProfileChanged(recordedUsrData);
          Log::dat(Log::Normal, "DataManager::onUsrEntered()", "user profile changed");
        }
    }
  else if(GlobalData::offline_usr_data_hash.contains(usrProfileStruct.key))
    {
      Log::dat(Log::Normal, "DataManager::onUsrEntered()", "incoming user already exist in offline list");
      GlobalData::online_usr_data_hash.insert(usrProfileStruct.key, GlobalData::offline_usr_data_hash.value(usrProfileStruct.key));
      UsrData *recordedUsrData = GlobalData::online_usr_data_hash.value(usrProfileStruct.key);
      if(usrProfileStruct != *recordedUsrData->getUsrProfileStruct())
        {
          recordedUsrData->setUsrProfileStruct(usrProfileStruct);
          updateUsr(usrProfileStruct);
          emit usrProfileChanged(recordedUsrData);
          Log::dat(Log::Normal, "DataManager::onUsrEntered()", "user profile changed");
        }
    }
  else
    {
      UsrData *userData = new UsrData(&GlobalData::settings_struct.profile_key_str, usrProfileStruct, this);
      GlobalData::online_usr_data_hash.insert(usrProfileStruct.key, userData);
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
      GlobalData::online_usr_data_hash.value(messageStruct.reciever)->addUnreadMessage(messageStruct);
    }
  else
    {
      qDebug()<<"notfromme";
      GlobalData::online_usr_data_hash.value(messageStruct.sender)->addUnreadMessage(messageStruct);
    }
  emit messageLoaded(messageStruct, fromMe);
}

void AppDataManager::onUpdatesAvailable()
{
  if(GlobalData::update_struct.version[0] == 0
     && GlobalData::update_struct.version[1] == 0
     && GlobalData::update_struct.version[2] == 0)
    {
      return;
    }

  QFile file(GlobalData::update_file_dir);
  if(!file.open(QIODevice::ReadWrite | QIODevice::Text))
    {
      return;
    }

  QTextStream in(&file);
  QTextStream out(&file);
  QByteArray inByteArray = in.readAll().toUtf8();
  int writeVersion[3];
  memcpy(&writeVersion, &GlobalData::current_version, sizeof(GlobalData::current_version));

  if(!inByteArray.isEmpty())
    {
      QJsonParseError jsonError;
      QJsonDocument readJsonDocument = QJsonDocument::fromJson(inByteArray, &jsonError);
      if(jsonError.error == QJsonParseError::NoError)
        {
          if(readJsonDocument.isObject())
            {
              QJsonObject readJsonObj = readJsonDocument.object();

              int read_version[3] = {
                readJsonObj.value("stable_version").toInt(),
                readJsonObj.value("beta_version").toInt(),
                readJsonObj.value("alpha_version").toInt()
              };

              for(int i = 0; i < 3; i ++)
                {
                  writeVersion[i] = read_version[i];
                }

              if(memcmp(read_version,
                        GlobalData::update_struct.version,
                        sizeof(read_version)) == 0)
                {
                  file.close();
                  file.flush();
                  emit updatesAvailable();

                  return;
                }
              else
                {
                  if(GlobalData::versionCompare(GlobalData::update_struct.version, read_version))
                    {
                      for(int i = 0; i < 3; i ++)
                        {
                          writeVersion[i] = GlobalData::update_struct.version[i];
                        }
                    }
                }
            }
        }
    }

  file.resize(0);

  out << makeUpdateJson(writeVersion).toJson(QJsonDocument::Indented) << endl;

  file.close();
  file.flush();

  emit updatesAvailable();
}

void AppDataManager::checkFiles()
{
  checkDir(GlobalData::data_location_dir);
  checkDir(GlobalData::user_data_dir);
  checkDir(GlobalData::log_dir);
}

bool AppDataManager::checkDir(const QString &directory)
{
  QDir dir(directory);
  if(!dir.exists())
    {
//      qDebug()<<"bool DataManager::ckeckDir(QString directory) NOT EXIST~";
      if(!dir.mkdir(directory))
        {
//          qDebug()<<"bool DataManager::ckeckDir(QString directory) CANT MAKE DIR!";
          return false;
        }
    }
  return true;
}

QJsonDocument AppDataManager::makeDefaultSettings()
{
  GlobalData::settings_struct.profile_key_str = makeUuid();
  GlobalData::settings_struct.profile_avatar_str = ":/avatar/avatar/default.png";
  GlobalData::settings_struct.profile_name_str = QHostInfo::localHostName();


  QJsonObject usrProfileJson;
  usrProfileJson.insert("usrKey", GlobalData::settings_struct.profile_key_str);
  usrProfileJson.insert("usrName", GlobalData::settings_struct.profile_name_str);
  usrProfileJson.insert("avatarPath", GlobalData::settings_struct.profile_avatar_str);
  usrProfileJson.insert("BubbleColorI", GlobalData::color_defaultChatBubbleI.name());
  usrProfileJson.insert("BubbleColorO", GlobalData::color_defaultChatBubbleO.name());

  ////these default data will be integrated in a class[I don't know what I meat in this comment...]

  QJsonDocument writeJsonDocument;
  writeJsonDocument.setObject(usrProfileJson);

  return writeJsonDocument;
}

QString AppDataManager::makeUuid()
{
//  const char alphabet_char[64] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_";
//  qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
//  GlobalData::settings_struct.profile_key_str.clear();

//  for(int i = 0; i < 32; i ++)
//    {
//      GlobalData::settings_struct.profile_key_str.append(alphabet_char[qrand()%63]);
//    }

  return QUuid::createUuid().toString();
}

void AppDataManager::initVariable()
{
  /*! When adding global variable to settings, choose a map with corresponding data type below.
   *  When adding new types, you need to add corresponding hash table for that type, go to register in readSettings() and writeSettings() to enable reading from disk.
   */
  settings_int_hash = {
    { "window_width", &GlobalData::settings_struct.window_width },
    { "window_height", &GlobalData::settings_struct.window_height }
  };

  settings_qcolor_hash = {
    { "BubbleColorI", &GlobalData::settings_struct.chat_bubble_color_i},
    { "BubbleColorO", &GlobalData::settings_struct.chat_bubble_color_o }
  };

  settings_qstring_hash = {
    { "usrKey", &GlobalData::settings_struct.profile_key_str },
    { "usrName", &GlobalData::settings_struct.profile_name_str },
    { "avatarPath", &GlobalData::settings_struct.profile_avatar_str }
  };

  settings_bool_hash = {
    { "updateNotification", &GlobalData::settings_struct.notification.update_notification },
    { "messageNotification", &GlobalData::settings_struct.notification.message_notification },
    { "messageDetailNotification", &GlobalData::settings_struct.notification.message_detail_notification },
    { "autoUpdate", &GlobalData::settings_struct.update.auto_update },
    { "autoCheckUpdate", &GlobalData::settings_struct.update.auto_check_update }
  };

  //defaults:
  GlobalData::settings_struct.chat_bubble_color_i = GlobalData::color_defaultChatBubbleI;
  GlobalData::settings_struct.chat_bubble_color_o = GlobalData::color_defaultChatBubbleO;
  GlobalData::settings_struct.notification.message_detail_notification = true;
  GlobalData::settings_struct.notification.message_notification = true;
  GlobalData::settings_struct.notification.update_notification = true;
  GlobalData::settings_struct.update.auto_check_update = true;
  GlobalData::settings_struct.update.auto_update = true;

}

void AppDataManager::readSettings()
{
  QFile file(GlobalData::settings_file_dir);
  if(!file.open(QIODevice::ReadWrite | QIODevice::Text))
    {
      return;
    }
  QTextStream in(&file);
  QTextStream out(&file);

  QByteArray inByteArray = in.readAll().toUtf8();
  QJsonParseError jsonError;
  QJsonDocument document = QJsonDocument::fromJson(inByteArray, &jsonError);
  if(jsonError.error == QJsonParseError::NoError)
    {
      if(document.isObject())
        {
          QJsonObject settingsJson = document.object();

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
  QFile file(GlobalData::contacts_file_dir);
  if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
      return;
    }
  QTextStream in(&file);
  QByteArray inByteArray = in.readAll().toUtf8();

  ///JSon
  QJsonParseError jsonError;
  QJsonDocument readJsonDocument = QJsonDocument::fromJson(inByteArray, &jsonError);
  if(jsonError.error == QJsonParseError::NoError)
    {
      if(readJsonDocument.isObject())
        {
          QJsonObject usrListJsonObj = readJsonDocument.object();
          QStringList usrKeyStrList = usrListJsonObj.keys();  //get usr_key as a string list

          for(int i = 0; i < usrKeyStrList.count(); i++)
            {
              QString *tempUsrKeyStr = &usrKeyStrList[i];
              QJsonObject tempUsrProfileJsonObj = usrListJsonObj[*tempUsrKeyStr].toObject();

              UsrProfileStruct usrProfileStruct;
              usrProfileStruct.key = tempUsrProfileJsonObj["usrKey"].toString();
              usrProfileStruct.name = tempUsrProfileJsonObj["usrName"].toString();
              usrProfileStruct.avatar = tempUsrProfileJsonObj["avatarPath"].toString();

              UsrData *usrData = new UsrData(&GlobalData::settings_struct.profile_key_str, usrProfileStruct, this);
              GlobalData::offline_usr_data_hash.insert(*tempUsrKeyStr, usrData);
            }
        }
    }
  else
    {
      qDebug()<<"&DataManager::loadUsrList(): Usr list file broken... Resize to 0.";
      file.resize(0);
      return;
    }

  file.flush();
  file.close();
}

void AppDataManager::writeSettings()
{
  QFile file(GlobalData::settings_file_dir);
  if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
      return;
    }

  QTextStream out(&file);

  QJsonObject settingsJson;

  for (std::pair<QString, int*> element : settings_int_hash)
    settingsJson.insert(element.first, *element.second);

  for (std::pair<QString, QColor*> element : settings_qcolor_hash)
    settingsJson.insert(element.first, element.second->name());

  for (std::pair<QString, QString*> element : settings_qstring_hash)
    settingsJson.insert(element.first, *element.second);

  for (std::pair<QString, bool*> element : settings_bool_hash)
    settingsJson.insert(element.first, *element.second);

  QJsonDocument writeJsonDocument;
  writeJsonDocument.setObject(settingsJson);

  file.resize(0);
  out << writeJsonDocument.toJson();
  Log::dat(Log::Normal, "AppDataManager::writeCurrentConfig()", "Config file updated.");
  file.flush();
  file.close();
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
  int font_id;
  QString font_family;

  font_id = QFontDatabase::addApplicationFont(":/font/font/GillSans.ttc");
  if(font_id == -1)
    {
      return;
    }

  font_family = QFontDatabase::applicationFontFamilies(font_id).at(0);

  GlobalData::font_chatTextEditor = QFont(font_family, 16);
  if(font_id == -1)
    {
      return;
    }

  font_id = QFontDatabase::addApplicationFont(":/font/font/Futura.ttc");
  font_family = QFontDatabase::applicationFontFamilies(font_id).at(0);
  GlobalData::font_main = QFont(font_family);
  GlobalData::font_chatBubble = GlobalData::font_main;
  GlobalData::font_chatBubble.setPointSize(14);
  GlobalData::font_combWidgetUsrName = GlobalData::font_main;
  GlobalData::font_combWidgetUsrName.setPointSize(15);
  GlobalData::font_combWidgetIpAddr = GlobalData::font_main;
  GlobalData::font_combWidgetIpAddr.setPointSize(11);
  GlobalData::font_menuButton = GlobalData::font_main;
  GlobalData::font_menuButton.setPointSize(14);
  GlobalData::font_scrollStackTitle = GlobalData::font_main;
  GlobalData::font_scrollStackTitle.setPointSize(15);
  GlobalData::font_scrollStackSubtitle = GlobalData::font_main;
  GlobalData::font_scrollStackSubtitle.setPointSize(13);

#endif //Q_OS_WIN

}

void AppDataManager::loadUpdates()
{
  QFile file(GlobalData::update_file_dir);
  if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
      return;
    }

  QTextStream in(&file);
  QByteArray inByteArray = in.readAll().toUtf8();

  if(!inByteArray.isEmpty())
    {
      QJsonParseError jsonError;
      QJsonDocument readJsonDocument = QJsonDocument::fromJson(inByteArray, &jsonError);
      if(jsonError.error == QJsonParseError::NoError)
        {
          if(readJsonDocument.isObject())
            {
              QJsonObject readJsonObj = readJsonDocument.object();

              int readVersion[3] = {
                readJsonObj.value("stable_version").toInt(),
                readJsonObj.value("beta_version").toInt(),
                readJsonObj.value("alpha_version").toInt()
              };

              if(GlobalData::versionCompare(GlobalData::current_version, readVersion))
                {
                  for(int i = 0; i < 3; i ++)
                    {
                      GlobalData::update_struct.version[i] = readVersion[i];
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



