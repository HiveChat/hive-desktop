#include "ThreadData.h"

ThreadData::ThreadData(QObject *parent) : QThread(parent)
{
  initVariable();
  checkFiles();
  loadMyProfile();
  loadFonts();

  TEST_SECTION();

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
          refreshGui();
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
  if(written_settings_struct != GlobalData::g_settings_struct)
    {
      qDebug()<<"&ThreadData::checkSettings():    written!!!!";
      writeCurrentConfig();
      written_settings_struct = GlobalData::g_settings_struct;
    }
}

void ThreadData::refreshGui()
{
  emit refreshGuiInfo();
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
  QFile file(usr_list_file_path);
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
  QFile file(usr_list_file_path);
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
  if(GlobalData::online_usr_data_map.keys().contains(usrProfileStruct->key_str))
    {
      qDebug()<<"@ThreadData::onUsrEntered: Incoming user already exist.";

      if(*usrProfileStruct != *GlobalData::online_usr_data_map.value(usrProfileStruct->key_str)->usrProfileStruct())
        {
          GlobalData::online_usr_data_map.value(usrProfileStruct->key_str)->setUsrProfileStruct(*usrProfileStruct);

          GlobalData::TEST_printUsrProfileStruct(*GlobalData::online_usr_data_map.value(usrProfileStruct->key_str)->usrProfileStruct(), "Thread Data packaging...");
          qDebug()<<"@ThreadData::onUsrEntered: User profile Changed.";
          emit usrProfileChanged(GlobalData::online_usr_data_map.value(usrProfileStruct->key_str));
        }
    }
  else
    {
      UsrData *user_data = new UsrData(&GlobalData::g_settings_struct.profile_key_str, *usrProfileStruct, this);
      GlobalData::online_usr_data_map.insert(usrProfileStruct->key_str, user_data);

      GlobalData::TEST_printUsrProfileStruct(*GlobalData::online_usr_data_map.value(usrProfileStruct->key_str)->usrProfileStruct(), "ThreadData Just packaged");
      qDebug()<<"@ThreadData::onUsrEntered: User profile Created.";
      emit usrProfileLoaded(GlobalData::online_usr_data_map.value(usrProfileStruct->key_str));

    }

  return;
}

void ThreadData::onUsrLeft(QString *usrKey)
{

}

void ThreadData::onMessageCome(MessageStruct *messageStruct, bool fromMe)
{
  if(fromMe)
    {
      GlobalData::online_usr_data_map.value(messageStruct->reciever_key)->addUnreadMessage(*messageStruct);
    }
  else
    {
      GlobalData::online_usr_data_map.value(messageStruct->sender_key)->addUnreadMessage(*messageStruct);
    }
  emit messageLoaded(*messageStruct, fromMe);
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
  GlobalData::g_settings_struct.profile_avatar_str = ":/avatar/avatar/default.png";
  GlobalData::g_settings_struct.profile_name_str = QHostInfo::localHostName();
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

QString ThreadData::appDataLocalPath()
{
  return QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
}

QJsonDocument ThreadData::makeUsrProfile()
{
  loadDefaultGlobalData();

  QJsonObject my_profile_json_obj;
  foreach (QString attribute, myProfileConfigJsonMap.keys())
    {
      my_profile_json_obj.insert(attribute, *myProfileConfigJsonMap.value(attribute));
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
  GlobalData::g_settings_struct.profile_key_str.clear();

  for(int i = 0; i < 32; i ++)
    {
      GlobalData::g_settings_struct.profile_key_str.append(alphabet_char[qrand()%63]);
    }

  qDebug()<<GlobalData::g_settings_struct.profile_key_str;
}

void ThreadData::initVariable()
{
  myProfileConfigJsonMap.insert("usrKey", &GlobalData::g_settings_struct.profile_key_str);
  myProfileConfigJsonMap.insert("usrName", &GlobalData::g_settings_struct.profile_name_str);
  myProfileConfigJsonMap.insert("avatarPath", &GlobalData::g_settings_struct.profile_avatar_str);
  myColorConfigJsonMap.insert("BubbleColorI", &GlobalData::g_settings_struct.chat_bubble_color_i);
  myColorConfigJsonMap.insert("BubbleColorO", &GlobalData::g_settings_struct.chat_bubble_color_o);

  GlobalData::g_settings_struct.chat_bubble_color_i = GlobalData::color_defaultChatBubbleI;
  GlobalData::g_settings_struct.chat_bubble_color_o = GlobalData::color_defaultChatBubbleO;
}

void ThreadData::initPalette()
{

}


void ThreadData::loadMyProfile()
{
  QFile file(my_profile_file_path);
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

          foreach(QString *global_data_ptr, myProfileConfigJsonMap.values())
            {
              *global_data_ptr = usr_list_json_obj[myProfileConfigJsonMap.key(global_data_ptr)].toString();
            }

          foreach(QColor *global_data_ptr, myColorConfigJsonMap.values())
            {
              qDebug()<<usr_list_json_obj[myColorConfigJsonMap.key(global_data_ptr)].toString();
              *global_data_ptr = QColor(usr_list_json_obj[myColorConfigJsonMap.key(global_data_ptr)].toString());
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

  written_settings_struct = GlobalData::g_settings_struct;

  file.flush();
  file.close();
}

void ThreadData::loadUsrList()
{
  QFile file(usr_list_file_path);
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
  qDebug()<<"void DataManager::writeCurrentConfig() invoked";

  QFile file(my_profile_file_path);
  if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
      return;
    }

  QTextStream out(&file);

  QJsonObject my_profile_json_obj;
  foreach (QString attribute, myProfileConfigJsonMap.keys())
    {
      my_profile_json_obj.insert(attribute, *myProfileConfigJsonMap.value(attribute));
    }

  my_profile_json_obj.insert("BubbleColorI", GlobalData::g_settings_struct.chat_bubble_color_i.name());
  my_profile_json_obj.insert("BubbleColorO", GlobalData::g_settings_struct.chat_bubble_color_o.name());

  ////these default data will be integrated in a class[I don't know what I meat in this comment...]

  QJsonDocument write_json_document;
  write_json_document.setObject(my_profile_json_obj);

  file.resize(0);
  out << write_json_document.toJson();
//  qDebug()<<write_json_document.toJson();
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
