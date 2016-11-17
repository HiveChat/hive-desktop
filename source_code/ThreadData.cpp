#include "ThreadData.h"

ThreadData::ThreadData(QObject *parent) : QThread(parent)
{
  initVariable();
  checkFiles();
  loadMySettings();
  loadFonts();

  TEST_SECTION();

	qDebug()<<this->currentThreadId();
  this->setParent(parent);
}

/////////////thread
ThreadData::~ThreadData()
{
  QMutex mutex;
  mutex.lock();
  running = false;
  mutex.unlock();

  qDebug()<<"ThreadData destructed";
}

void ThreadData::run()
{
  QMutex mutex;
  while(this->isRunning())
    {
      mutex.lock();

      if(loop_count%1 == 0)//every 1 second
        {

        }
      if(loop_count%2 == 0)//every 2 second
        {
          checkSettings();
        }
      if(loop_count%5 == 0)//every 5 second
        {

        }
      if(loop_count%10 == 0)//every 10 second
        {
          loop_count = 0;
        }

      loop_count ++;
      mutex.unlock();
      msleep(1000);
    }
}

void ThreadData::checkSettings()
{
//  if(written_settings_struct != GlobalData::g_settings_struct)
//    {
//      qDebug()<<"&ThreadData::checkSettings():    written!!!!";
//      writeCurrentConfig();
//      written_settings_struct = GlobalData::g_settings_struct;
//    }
  if(GlobalData::settings_struct.modified_lock)
    {
      qDebug()<<"&ThreadData::checkSettings(): Settings changed";
      writeCurrentConfig();
      GlobalData::settings_struct.modified_lock = false;
//      written_settings_struct = GlobalData::g_settings_struct;

    }
}

QJsonObject ThreadData::makeUsrProfile(UsrProfileStruct &usrProfileStruct)
{
  QJsonObject profile_json_obj;
  profile_json_obj.insert("usrName", usrProfileStruct.name_str);
  profile_json_obj.insert("avatarPath", usrProfileStruct.avatar_str);

  QJsonObject usr_profile_json_obj;
  usr_profile_json_obj.insert(usrProfileStruct.key_str, profile_json_obj);

  return usr_profile_json_obj;
}

QJsonDocument ThreadData::makeUsrList(QList<QJsonObject> &usr_profile_list)
{
  QJsonArray usr_list_json_array;
  foreach (QJsonObject json_obj, usr_profile_list)
    {
      usr_list_json_array.append(json_obj);
    }
  QJsonDocument json_doc;
  json_doc.setArray(usr_list_json_array);

  return json_doc;
}

QJsonDocument ThreadData::makeUpdateJson(const int stable[])
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


void ThreadData::TEST_SECTION()
{
  //addUsr(&GlobalData::g_settings_struct);
}

void ThreadData::addUsr(UsrProfileStruct *usrProfileStruct)
{
  QString usr_key = usrProfileStruct->key_str;
  QString ip_addr = usrProfileStruct->ip_str;
  QString usr_name = usrProfileStruct->name_str;
  QString avatar_path = usrProfileStruct->avatar_str;

  qDebug()<<ip_addr;

  ///usrKey<<usrName<<ipAddr<<avatarPath
  QFile file(contacts_file_path);
  if(!file.open(QIODevice::ReadWrite | QIODevice::Text))
    {
      return;
    }

  QTextStream in(&file);
  QByteArray in_byte_array = in.readAll().toUtf8();

  QTextStream out(&file);



  ///JSon
  QJsonParseError json_error;
  QJsonDocument read_json_document = QJsonDocument::fromJson(in_byte_array, &json_error);
  if(json_error.error == QJsonParseError::NoError)
    {
      if(read_json_document.isObject())
        {
          QJsonObject usr_list_json_obj = read_json_document.object();
          if(!usr_list_json_obj.contains(usr_key))
            {
              QJsonObject usr_info_json_obj;
              usr_info_json_obj.insert("usrKey", usr_key);
              usr_info_json_obj.insert("usrName", usr_name);
              usr_info_json_obj.insert("avatarPath", avatar_path);

              usr_list_json_obj.insert(usr_key, usr_info_json_obj);

              QJsonDocument write_json_document;
              write_json_document.setObject(usr_list_json_obj);

              file.resize(0);
              out<<write_json_document.toJson()<<endl;
            }
        }
    }
  else
    {

      qDebug()<<"else";
      QJsonObject usr_info_json_obj;
//      usr_info_json_obj.insert("ipAddr", ip_addr);
      usr_info_json_obj.insert("usrKey", usr_key);
      usr_info_json_obj.insert("usrName", usr_name);
      usr_info_json_obj.insert("avatarPath", avatar_path);

      QJsonObject usr_list_json_obj;
      usr_list_json_obj.insert(usr_key, usr_info_json_obj);

      QJsonDocument write_json_document;
      write_json_document.setObject(usr_list_json_obj);

      file.resize(0); //clear all
      ///QJsonDocument::Compact
      out<<write_json_document.toJson(QJsonDocument::Indented);
//      qDebug()<<write_json_document.toJson(QJsonDocument::Compact);
    }


  file.flush();
  file.close();

}

void ThreadData::deleteUsr(const QStringList usrInfoStrList)
{
  QFile file(contacts_file_path);
  if(!file.open(QIODevice::ReadWrite | QIODevice::Text))
  {
    return;
  }

  QTextStream in(&file);
  QTextStream out(&file);

  QByteArray in_byte_array = in.readAll().toUtf8();

  ///JSon
  QJsonParseError json_error;
  QJsonDocument read_json_document = QJsonDocument::fromJson(in_byte_array, &json_error);
  if(json_error.error == QJsonParseError::NoError)
    {
      if(read_json_document.isObject())
        {
          QJsonObject usr_list_json_obj = read_json_document.object();
          usr_list_json_obj.erase(usr_list_json_obj.find(usrInfoStrList.at(0)));

          QJsonDocument write_json_document;
          write_json_document.setObject(usr_list_json_obj);
          file.resize(0);
          out<<write_json_document.toJson(QJsonDocument::Indented)<<endl;

        }
    }
  else
    {
      qDebug()<<"Contact delete failed, is file empty?";

    }

  file.close();
  file.flush();
}

void ThreadData::onUsrEntered(UsrProfileStruct *usrProfileStruct)
{
  if(GlobalData::online_usr_data_hash.keys().contains(usrProfileStruct->key_str))
    {
      qDebug()<<"@ThreadData::onUsrEntered: Incoming user already exist.";

      if(*usrProfileStruct != *GlobalData::online_usr_data_hash.value(usrProfileStruct->key_str)->usrProfileStruct())
        {
          GlobalData::online_usr_data_hash.value(usrProfileStruct->key_str)->setUsrProfileStruct(*usrProfileStruct);

          GlobalData::TEST_printUsrProfileStruct(*GlobalData::online_usr_data_hash.value(usrProfileStruct->key_str)->usrProfileStruct(), "Thread Data packaging...");
          qDebug()<<"@ThreadData::onUsrEntered: User profile Changed.";
          emit usrProfileChanged(GlobalData::online_usr_data_hash.value(usrProfileStruct->key_str));
        }
    }
  else
    {
      UsrData *user_data = new UsrData(&GlobalData::settings_struct.profile_key_str, *usrProfileStruct, this);
      GlobalData::online_usr_data_hash.insert(usrProfileStruct->key_str, user_data);

      GlobalData::TEST_printUsrProfileStruct(*GlobalData::online_usr_data_hash.value(usrProfileStruct->key_str)->usrProfileStruct(), "ThreadData Just packaged");
      qDebug()<<"@ThreadData::onUsrEntered: User profile Created.";
      emit usrProfileLoaded(GlobalData::online_usr_data_hash.value(usrProfileStruct->key_str));

    }

  return;
}

void ThreadData::onUsrLeft(QString *usrKey)
{

}

void ThreadData::onMessageCome(Message::TextMessageStruct *messageStruct, bool fromMe)
{
  if(fromMe)
    {
      GlobalData::online_usr_data_hash.value(messageStruct->reciever)->addUnreadMessage(*messageStruct);
    }
  else
    {
      GlobalData::online_usr_data_hash.value(messageStruct->sender)->addUnreadMessage(*messageStruct);
    }
  emit messageLoaded(*messageStruct, fromMe);
}

void ThreadData::onUpdatesAvailable()
{
  if(GlobalData::update_struct.version[0] == 0
     && GlobalData::update_struct.version[1] == 0
     && GlobalData::update_struct.version[2] == 0)
    {
      return;
    }

  QFile file(update_file_path);
  if(!file.open(QIODevice::ReadWrite | QIODevice::Text))
    {
      return;
    }

  QTextStream in(&file);
  QTextStream out(&file);
  QByteArray in_byte_array = in.readAll().toUtf8();
  int write_version[3];

  if(!in_byte_array.isEmpty())
    {
      QJsonParseError json_error;
      QJsonDocument read_json_document = QJsonDocument::fromJson(in_byte_array, &json_error);
      if(json_error.error == QJsonParseError::NoError)
        {
          if(read_json_document.isObject())
            {
              QJsonObject read_json_obj = read_json_document.object();

              int read_version[3] = {
                read_json_obj.value("stable_version").toInt(),
                read_json_obj.value("beta_version").toInt(),
                read_json_obj.value("alpha_version").toInt()
              };

              for(int i = 0; i < 3; i ++)
                {
                  write_version[i] = read_version[i];
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
													write_version[i] = GlobalData::update_struct.version[i];
												}
										}
                }
            }
        }
		}

  out << makeUpdateJson(write_version).toJson(QJsonDocument::Indented) << endl;

  file.close();
	file.flush();

  emit updatesAvailable();
}

void ThreadData::checkFiles()
{
  checkDir(app_data_local_path);
  checkDir(usr_path);
  checkDir(log_path);
}

void ThreadData::loadDefaultGlobalData()
{
  makeUsrKey();
  GlobalData::settings_struct.profile_avatar_str = ":/avatar/avatar/default.png";
  GlobalData::settings_struct.profile_name_str = QHostInfo::localHostName();
}


bool ThreadData::checkDir(const QString &directory)
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

//QString ThreadData::appDataLocalPath()
//{
//  return QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
//}

QJsonDocument ThreadData::makeUsrProfile()
{
  loadDefaultGlobalData();

  QJsonObject my_profile_json_obj;
  foreach (QString attribute, settings_map_qstring.keys())
    {
      my_profile_json_obj.insert(attribute, QJsonValue::fromVariant(*settings_map_qstring.value(attribute)));
    }

  my_profile_json_obj.insert("BubbleColorI", GlobalData::color_defaultChatBubbleI.name());
  my_profile_json_obj.insert("BubbleColorO", GlobalData::color_defaultChatBubbleO.name());

  ////these default data will be integrated in a class[I don't know what I meat in this comment...]

  QJsonDocument write_json_document;
  write_json_document.setObject(my_profile_json_obj);

  return write_json_document;
}

void ThreadData::makeUsrKey()
{
  const char alphabet_char[64] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_";
  qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
  GlobalData::settings_struct.profile_key_str.clear();

  for(int i = 0; i < 32; i ++)
    {
      GlobalData::settings_struct.profile_key_str.append(alphabet_char[qrand()%63]);
    }

  qDebug()<<GlobalData::settings_struct.profile_key_str;
}

void ThreadData::initVariable()
{
  //When adding global variable to settings, choose a map with corresponding data type below.
  //When adding map, go to register in loadMySettings() to enable reaing from disk.
  settings_map_qstring.insert("usrKey",
                              &GlobalData::settings_struct.profile_key_str);
  settings_map_qstring.insert("usrName",
                              &GlobalData::settings_struct.profile_name_str);
  settings_map_qstring.insert("avatarPath",
                              &GlobalData::settings_struct.profile_avatar_str);

  settings_map_qcolor.insert("BubbleColorI",
                             &GlobalData::settings_struct.chat_bubble_color_i);
  settings_map_qcolor.insert("BubbleColorO",
                             &GlobalData::settings_struct.chat_bubble_color_o);

  settings_map_bool.insert("updateNotification",
                           &GlobalData::settings_struct.notification.update_notification);
  settings_map_bool.insert("messageNotification",
                           &GlobalData::settings_struct.notification.message_notification);
  settings_map_bool.insert("messageDetailNotification",
                           &GlobalData::settings_struct.notification.message_detail_notification);
  settings_map_bool.insert("autoUpdate",
                           &GlobalData::settings_struct.update.auto_update);
  settings_map_bool.insert("autoCheckUpdate",
                           &GlobalData::settings_struct.update.auto_check_update);

  //defaults:
  GlobalData::settings_struct.chat_bubble_color_i = GlobalData::color_defaultChatBubbleI;
  GlobalData::settings_struct.chat_bubble_color_o = GlobalData::color_defaultChatBubbleO;
  GlobalData::settings_struct.notification.message_detail_notification = true;
  GlobalData::settings_struct.notification.message_notification = true;
  GlobalData::settings_struct.notification.update_notification = true;
  GlobalData::settings_struct.update.auto_check_update = true;
  GlobalData::settings_struct.update.auto_update = true;

}

void ThreadData::loadMySettings()
{
  QFile file(settings_file_path);
  if(!file.open(QIODevice::ReadWrite | QIODevice::Text))
    {
      return;
    }

  QTextStream in(&file);
  QTextStream out(&file);
  QByteArray in_byte_array = in.readAll().toUtf8();

  QJsonParseError json_error;
  QJsonDocument read_json_document = QJsonDocument::fromJson(in_byte_array, &json_error);
  if(json_error.error == QJsonParseError::NoError)
    {
      if(read_json_document.isObject())
        {
          QJsonObject usr_list_json_obj = read_json_document.object();

          //This is Tim's magic
          foreach(QString *var, settings_map_qstring.values())
            {
              *var = usr_list_json_obj[settings_map_qstring.key(var)].toString();
            }

          foreach(QColor *var, settings_map_qcolor.values())
            {
              *var = QColor(usr_list_json_obj[settings_map_qcolor.key(var)].toString());
            }

          foreach(bool *var, settings_map_bool.values())
            {
              *var = usr_list_json_obj[settings_map_bool.key(var)].toBool();
            }
        }
      else
        {
          file.resize(0);
          out<<makeUsrProfile().toJson(QJsonDocument::Indented)<<endl;
        }
    }
  else
    {
      file.resize(0);
      out<<makeUsrProfile().toJson(QJsonDocument::Indented)<<endl;
    }

//  written_settings_struct = GlobalData::g_settings_struct;

  file.flush();
  file.close();
}

void ThreadData::loadUsrList()
{
  QFile file(contacts_file_path);
  if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
      return;
    }
  QTextStream in(&file);
  QByteArray in_byte_array = in.readAll().toUtf8();

  ///JSon
  QJsonParseError json_error;
  QJsonDocument read_json_document = QJsonDocument::fromJson(in_byte_array, &json_error);
  if(json_error.error == QJsonParseError::NoError)
    {
      if(read_json_document.isObject())
        {
          QJsonObject usr_list_json_obj = read_json_document.object();
          QStringList usr_key_str_list = usr_list_json_obj.keys();  //get usr_key as a string list

          for(int i = 0; i < usr_key_str_list.count(); i++)
            {
              QString *temp_usr_key_str = &usr_key_str_list[i];
              QJsonObject temp_usr_profile_json_obj = usr_list_json_obj[*temp_usr_key_str].toObject();

              UsrProfileStruct usr_profile_struct;
              usr_profile_struct.key_str = temp_usr_profile_json_obj["usrKey"].toString();
              usr_profile_struct.name_str = temp_usr_profile_json_obj["usrName"].toString();
              usr_profile_struct.avatar_str = temp_usr_profile_json_obj["avatarPath"].toString();

              local_usr_profile_map.insert(*temp_usr_key_str, usr_profile_struct);
              ////////////must enable!!!!!!!!
//              emit usrProfileLoaded(&usr_profile_struct);
            }
        }
    }
  else
    {
      qDebug()<<"&ThreadData::loadUsrList(): Usr list file broken... Resize to 0.";
      file.resize(0);
      return;
    }

  file.flush();
  file.close();
}

void ThreadData::writeCurrentConfig()
{
  qDebug()<<"&DataManager::writeCurrentConfig() invoked";

  QFile file(settings_file_path);
  if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
      return;
    }

  QTextStream out(&file);

  QJsonObject my_profile_json_obj;
  foreach (QString attribute, settings_map_qstring.keys())
    {
      my_profile_json_obj.insert(attribute, *settings_map_qstring.value(attribute));
    }
  foreach (QString attribute, settings_map_qcolor.keys())
    {
      my_profile_json_obj.insert(attribute, settings_map_qcolor.value(attribute)->name());
    }
  foreach (QString attribute, settings_map_bool.keys())
    {
      my_profile_json_obj.insert(attribute, *settings_map_bool.value(attribute));
    }


//  my_profile_json_obj.insert("BubbleColorI", GlobalData::settings_struct.chat_bubble_color_i.name());
//  my_profile_json_obj.insert("BubbleColorO", GlobalData::settings_struct.chat_bubble_color_o.name());

  ////these default data will be integrated in a class[I don't know what I meat in this comment...]

  QJsonDocument write_json_document;
  write_json_document.setObject(my_profile_json_obj);

  file.resize(0);
  out << write_json_document.toJson();
  qDebug()<<".....................history written...................";
  file.flush();
  file.close();
}

void ThreadData::loadFonts()
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
  GlobalData::font_main = QFont(font_family, 10);
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

void ThreadData::loadUpdates()
{
	QFile file(update_file_path);
	if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
		{
			return;
		}

	QTextStream in(&file);
	QByteArray in_byte_array = in.readAll().toUtf8();

	if(!in_byte_array.isEmpty())
		{
			QJsonParseError json_error;
			QJsonDocument read_json_document = QJsonDocument::fromJson(in_byte_array, &json_error);
			if(json_error.error == QJsonParseError::NoError)
				{
					if(read_json_document.isObject())
						{
							QJsonObject read_json_obj = read_json_document.object();

							int read_version[3] = {
								read_json_obj.value("stable_version").toInt(),
								read_json_obj.value("beta_version").toInt(),
								read_json_obj.value("alpha_version").toInt()
							};

							if(GlobalData::versionCompare(GlobalData::current_version, read_version))
								{
									for(int i = 0; i < 3; i ++)
										{
											GlobalData::update_struct.version[i] = read_version[i];
										}
									emit updatesAvailable();
								}
						}
				}
		}

	file.close();
	file.flush();
}


/*
void encode(QString filename)
{
    QFile file(filename);
    QTextStream in(&file);
    QString str;
    if(file.open(QIODevice::ReadWrite))
    {
        str = in.readAll();
        qDebug() << str;

        int len = str.length();
        for(int i=0;i<len;++i)
        {
            str[i] = QChar::fromAscii(str[i].toAscii() - 1);

        }

        qDebug() << str;
    }
    file.close();

    QTextStream out(&file);
    file.open(QIODevice::WriteOnly);
    out << str;
    file.close();
}


void decode(QString filename)
{
    QFile file(filename);
    QTextStream fin(&file);
    QString str;
    if(file.open(QIODevice::ReadOnly))
    {
        str = fin.readAll();
        qDebug() << str;

        int len = str.length();
        for(int i=0;i<len;++i)
        {
            str[i] = QChar::fromAscii(str[i].toAscii() + 1);

        }

        qDebug() << str;
    }
    file.close();

    QTextStream fout(&file);
    file.open(QIODevice::WriteOnly);
    fout << str;
    file.close();
}
*/



//////slots
