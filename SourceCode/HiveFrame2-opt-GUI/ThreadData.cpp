#include "ThreadData.h"

ThreadData::ThreadData(QObject *parent) : QThread(parent)
{
  myProfileConfigJsonMap.insert("usrKey", &GlobalData::g_my_profile.key_str);
  myProfileConfigJsonMap.insert("usrName", &GlobalData::g_my_profile.name_str);
  myProfileConfigJsonMap.insert("avatarPath", &GlobalData::g_my_profile.avatar_str);
  myColorConfigJsonMap.insert("BubbleColorI", &GlobalData::g_mChatBubbleColorI);
  myColorConfigJsonMap.insert("BubbleColorO", &GlobalData::g_mChatBubbleColorO);

  b_mChatBubbleColorI = GlobalData::g_mChatBubbleColorI;
  b_mChatBubbleColorO = GlobalData::g_mChatBubbleColorO;
  b_myNameStr = GlobalData::g_my_profile.name_str;
  b_avatarPathStr = GlobalData::g_my_profile.avatar_str;

  checkData();
  loadMyProfile();
  loadFonts();

  TEST_SECTION();

  this->setParent(parent);
}

/////////////thread
ThreadData::~ThreadData()
{
  running = false;
}

void ThreadData::run()
{
  while(running)
    {
      checkSettings();

      msleep(1000);
    }
}

void ThreadData::checkSettings()
{
  if(b_mChatBubbleColorI != GlobalData::g_mChatBubbleColorI ||
     b_mChatBubbleColorO != GlobalData::g_mChatBubbleColorO ||
     b_myNameStr != GlobalData::g_my_profile.name_str ||
     b_avatarPathStr != GlobalData::g_my_profile.avatar_str)
    {
      b_mChatBubbleColorI = GlobalData::g_mChatBubbleColorI;
      b_mChatBubbleColorO = GlobalData::g_mChatBubbleColorO;
      b_myNameStr = GlobalData::g_my_profile.name_str;
      b_avatarPathStr = GlobalData::g_my_profile.avatar_str;

      writeCurrentConfig();
    }
}


///////////!thread

void ThreadData::TEST_SECTION()
{

  addUsr(&GlobalData::g_my_profile);
//  ///////////JOSN DATA
//  QStringList usrInfoStrList;
//  ////this cannot be MAC address Keep in mind!
////  usrInfoStrList<<"90-00-4E-9A-A4-FD"<<"192.168.1.1"<<"Bob"<<":/avatar/avatar/bee.png";
////  addUsr(usrInfoStrList);
////  usrInfoStrList.clear();
//  usrInfoStrList<<"44-00-9E-9A-A4-FD"<<"192.168.1.2"<<"James"<<":/avatar/avatar/ladybug.png";
//  addUsr(&usrInfoStrList);
//  usrInfoStrList.clear();
//  usrInfoStrList<<"20-00-9E-9A-A4-FD"<<"192.168.1.3"<<"Rob"<<":/avatar/avatar/fat.png";///r
//  addUsr(&usrInfoStrList);
//  usrInfoStrList.clear();
//  usrInfoStrList<<"0?-00-9E-9A-A4-FD"<<"192.168.1.4"<<"Paul"<<":/avatar/avatar/sunflower.png";
//  addUsr(&usrInfoStrList);
//  usrInfoStrList.clear();
//  usrInfoStrList<<"30-00-9E-9A-A4-FD"<<"192.168.1.5"<<"Tom"<<":/avatar/avatar/disk.png";
//  addUsr(&usrInfoStrList);
//  usrInfoStrList.clear();
//  usrInfoStrList<<"40-00-9E-9A-A4-FD"<<"192.168.1.6"<<"Levi"<<":/avatar/avatar/bee.png";
//  addUsr(&usrInfoStrList);
//  usrInfoStrList.clear();
////  usrInfoStrList<<"20-00-9E-9A-A4-FD"<<"192.168.1.7"<<"Peter"<<":/avatar/avatar/sunflower.png";///r
////  addUsr(usrInfoStrList);
////  usrInfoStrList.clear();
////  usrInfoStrList<<"11-00-9E-9A-A4-FD"<<"192.168.1.8"<<"Justin"<<":/avatar/avatar/worm.png";
////  addUsr(usrInfoStrList);
////  usrInfoStrList.clear();
//  usrInfoStrList<<"45-00-9E-9A-A4-FD"<<"192.168.1.9"<<"Nemo"<<":/avatar/avatar/worm.png";
//  addUsr(&usrInfoStrList);
//  usrInfoStrList.clear();
//  usrInfoStrList<<"87-00-9E-9A-A4-FD"<<"192.168.1.10"<<"Lynn"<<":/avatar/avatar/ladybug.png";
//  addUsr(&usrInfoStrList);
//  usrInfoStrList.clear();
//  usrInfoStrList<<"90-00-9E-9A-A4-FD"<<"192.168.1.11"<<"Timm"<<":/avatar/avatar/sunflower.png";
//  deleteUsr(usrInfoStrList);
//  ///////////!JSON DATA

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
//              usr_info_json_obj.insert("ipAddr", ip_addr);
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
//          qDebug()<<write_json_document.toJson(QJsonDocument::Indented);

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
  if(online_usr_profile_map.keys().contains(usrProfileStruct->key_str))
    {
      if(*usrProfileStruct != online_usr_profile_map.value(usrProfileStruct->key_str))
        {
          qDebug()<<"Avatar Changed to be"<<usrProfileStruct->avatar_str;
          online_usr_profile_map.remove(usrProfileStruct->key_str);
          emit usrProfileChanged(&online_usr_profile_map.insert(usrProfileStruct->key_str, *usrProfileStruct).value());
        }
      return;
    }
  else
    {
      online_usr_profile_map.insert(usrProfileStruct->key_str, *usrProfileStruct);
      emit usrProfileLoaded(&online_usr_profile_map.insert(usrProfileStruct->key_str, *usrProfileStruct).value());

      return;
    }
}

void ThreadData::onUsrLeft(QString *usrKey)
{

}

void ThreadData::checkData()
{
  checkDir(app_data_local_path);
  checkDir(usr_path);
  checkDir(log_path);
}

void ThreadData::loadDefaultGlobalData()
{
  makeUsrKey();
  GlobalData::g_my_profile.avatar_str = ":/avatar/avatar/default.png";
  GlobalData::g_my_profile.name_str = QHostInfo::localHostName();
}


bool ThreadData::checkDir(const QString directory)
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

QJsonDocument ThreadData::defaultProfile()
{
  loadDefaultGlobalData();

  QJsonObject my_profile_json_obj;
  foreach (QString attribute, myProfileConfigJsonMap.keys())
    {
      my_profile_json_obj.insert(attribute, *myProfileConfigJsonMap.value(attribute));
    }

  my_profile_json_obj.insert("BubbleColorI", GlobalData::g_chatBubbleColorI.name());
  my_profile_json_obj.insert("BubbleColorO", GlobalData::g_chatBubbleColorO.name());

  ////these default data will be integrated in a class[I don't know what I meat in this comment...]

  QJsonDocument write_json_document;
  write_json_document.setObject(my_profile_json_obj);

  return write_json_document;
}

void ThreadData::makeUsrKey()
{
  const char alphabet_char[64] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_";
  qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
  GlobalData::g_my_profile.key_str.clear();

  for(int i = 0; i < 32; i ++)
    {
      GlobalData::g_my_profile.key_str.append(alphabet_char[qrand()%63]);
    }

  qDebug()<<GlobalData::g_my_profile.key_str;
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
          out<<defaultProfile().toJson(QJsonDocument::Indented)<<endl;
        }
    }
  else
    {
      file.resize(0);
      out<<defaultProfile().toJson(QJsonDocument::Indented)<<endl;
    }

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

              localUsrProfileMap.insert(*temp_usr_key_str, usr_profile_struct);
              emit usrProfileLoaded(&usr_profile_struct);
            }
        }
    }
  else
    {
      qDebug()<<"@loadUsrList(): Usr list file broken... Resize to 0.";
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

  my_profile_json_obj.insert("BubbleColorI", GlobalData::g_mChatBubbleColorI.name());
  my_profile_json_obj.insert("BubbleColorO", GlobalData::g_mChatBubbleColorO.name());

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
  int fontId = QFontDatabase::addApplicationFont(":/font/font/Futura.ttc");
  QString msyh = QFontDatabase::applicationFontFamilies ( fontId ).at(0);
  GlobalData::g_font = QFont(msyh,10);
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


