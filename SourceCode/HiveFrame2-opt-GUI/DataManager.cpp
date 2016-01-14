#include "DataManager.h"

DataManager::DataManager(QObject *parent) : QObject(parent)
{
  checkData();
  loadMyProfile();

  TEST_SECTION();

  this->setParent(parent);
}

void DataManager::TEST_SECTION()
{


  ///////////JOSN DATA
  QStringList usrInfoStrList;
  ////this cannot be MAC address Keep in mind!
  usrInfoStrList<<"90:00:4E:9A:A4:FD"<<"192.168.1.1"<<"Bob"<<":/avatar/avatar/bee.png";
  addUsr(usrInfoStrList);
  usrInfoStrList.clear();
  usrInfoStrList<<"44:00:9E:9A:A4:FD"<<"192.168.1.2"<<"Tim"<<":/avatar/avatar/ladybug.png";
  addUsr(usrInfoStrList);
  usrInfoStrList.clear();
  usrInfoStrList<<"20:00:9E:9A:A4:FD"<<"192.168.1.3"<<"Rob"<<":/avatar/avatar/fat.png";///r
  addUsr(usrInfoStrList);
  usrInfoStrList.clear();
  usrInfoStrList<<"0?:00:9E:9A:A4:FD"<<"192.168.1.4"<<"Paul"<<":/avatar/avatar/sunflower.png";
  addUsr(usrInfoStrList);
  usrInfoStrList.clear();
  usrInfoStrList<<"30:00:9E:9A:A4:FD"<<"192.168.1.5"<<"Tom"<<":/avatar/avatar/disk.png";
  addUsr(usrInfoStrList);
  usrInfoStrList.clear();
  usrInfoStrList<<"40:00:9E:9A:A4:FD"<<"192.168.1.6"<<"Levi"<<":/avatar/avatar/bee.png";
  addUsr(usrInfoStrList);
  usrInfoStrList.clear();
  usrInfoStrList<<"20:00:9E:9A:A4:FD"<<"192.168.1.7"<<"Peter"<<":/avatar/avatar/sunflower.png";///r
  addUsr(usrInfoStrList);
  usrInfoStrList.clear();
  usrInfoStrList<<"11:00:9E:9A:A4:FD"<<"192.168.1.8"<<"Justin"<<":/avatar/avatar/worm.png";
  addUsr(usrInfoStrList);
  usrInfoStrList.clear();
  usrInfoStrList<<"45:00:9E:9A:A4:FD"<<"192.168.1.9"<<"Nemo"<<":/avatar/avatar/worm.png";
  addUsr(usrInfoStrList);
  usrInfoStrList.clear();
  usrInfoStrList<<"87:00:9E:9A:A4:FD"<<"192.168.1.10"<<"Lynn"<<":/avatar/avatar/ladybug.png";
  addUsr(usrInfoStrList);
  usrInfoStrList.clear();
  usrInfoStrList<<"90:00:9E:9A:A4:FD"<<"192.168.1.11"<<"Tim"<<":/avatar/avatar/sunflower.png";
  deleteUsr(usrInfoStrList);
  ///////////!JSON DATA

}

void DataManager::addUsr(QStringList usrInfoStrList)
{
  QString usr_key = usrInfoStrList.at(0);
  QString ip_addr = usrInfoStrList.at(1);
  QString usr_name = usrInfoStrList.at(2);
  QString avatar_path = usrInfoStrList.at(3);



  ///usrKey<<usrName<<ipAddr
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
  QJsonDocument read_json_doucment = QJsonDocument::fromJson(in_byte_array, &json_error);
  if(json_error.error == QJsonParseError::NoError)
    {
      if(read_json_doucment.isObject())
        {
          QJsonObject usr_list_json_obj = read_json_doucment.object();
          if(!usr_list_json_obj.contains(usr_key))
            {
              QJsonObject usr_info_json_obj;
              usr_info_json_obj.insert("ipAddr", ip_addr);
              usr_info_json_obj.insert("usrKey", usr_key);
              usr_info_json_obj.insert("usrName", usr_name);
              usr_info_json_obj.insert("avatarPath", avatar_path);



              usr_list_json_obj.insert(usr_key, usr_info_json_obj);

              QJsonDocument write_json_doucment;
              write_json_doucment.setObject(usr_list_json_obj);

              file.resize(0);
              out<<write_json_doucment.toJson(QJsonDocument::Compact)<<endl;
            }
        }
    }
  else
    {

      qDebug()<<"else";
      QJsonObject usr_info_json_obj;
      usr_info_json_obj.insert("ipAddr", ip_addr);
      usr_info_json_obj.insert("usrKey", usr_key);
      usr_info_json_obj.insert("usrName", usr_name);
      usr_info_json_obj.insert("avatarPath", avatar_path);

      QJsonObject usr_list_json_obj;
      usr_list_json_obj.insert(usr_key, usr_info_json_obj);

      QJsonDocument write_json_doucment;
      write_json_doucment.setObject(usr_list_json_obj);

      file.resize(0); //clear all
      out<<write_json_doucment.toJson(QJsonDocument::Compact)<<endl;
      qDebug()<<write_json_doucment.toJson(QJsonDocument::Compact);
    }


  file.flush();
  file.close();

}

void DataManager::deleteUsr(QStringList usrInfoStrList)
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
  QJsonDocument read_json_doucment = QJsonDocument::fromJson(in_byte_array, &json_error);
  if(json_error.error == QJsonParseError::NoError)
    {
      if(read_json_doucment.isObject())
        {
          QJsonObject usr_list_json_obj = read_json_doucment.object();
          usr_list_json_obj.erase(usr_list_json_obj.find(usrInfoStrList.at(0)));

          QJsonDocument write_json_doucment;
          write_json_doucment.setObject(usr_list_json_obj);
          file.resize(0);
          out<<write_json_doucment.toJson(QJsonDocument::Compact)<<endl;
          qDebug()<<write_json_doucment.toJson(QJsonDocument::Compact);

        }
    }
  else
    {
      qDebug()<<"Contact delete failed, is file empty?";

    }

  file.close();
  file.flush();
}


/*
QList<QStringList> DataManager::import_usr_form()
{
  return usr_form;
}
*/

void DataManager::checkData()
{
  checkDir(app_data_local_path);
  checkDir(usr_path);
  checkDir(log_path);
}


bool DataManager::checkDir(QString directory)
{
  QDir dir(directory);
  if(!dir.exists())
    {
      qDebug()<<"bool DataManager::ckeckDir(QString directory) NOT EXIST~";

      if(!dir.mkdir(directory))
        {
          qDebug()<<"bool DataManager::ckeckDir(QString directory) CANT MAKE DIR!";
          return false;
        }
    }
  return true;
}



QJsonDocument DataManager::defaultProfile()
{
  makeUsrKey();

  QJsonObject my_profile_json_obj;
  my_profile_json_obj.insert("usrKey", GlobalData::g_myKeyStr);
  my_profile_json_obj.insert("usrName", QHostInfo::localHostName());
  my_profile_json_obj.insert("avatarPath", ":/img/img/icon.png");
  ////these default data will be integrated in a class

  QJsonDocument write_json_doucment;
  write_json_doucment.setObject(my_profile_json_obj);
}

void DataManager::makeUsrKey()
{
  qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));

  for(int i = 0; i < 32; i ++)
    {
      GlobalData::g_myKeyStr.append(alphabet_char[qrand()%64]);
    }

  qDebug()<<GlobalData::g_myKeyStr;
}


void DataManager::loadMyProfile()
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
  QJsonDocument read_json_doucment = QJsonDocument::fromJson(in_byte_array, &json_error);
  if(json_error.error == QJsonParseError::NoError)
    {
      if(read_json_doucment.isObject())
        {
          QJsonObject usr_list_json_obj = read_json_doucment.object();

          GlobalData::g_myKeyStr = usr_list_json_obj["usrKey"].toString();
          GlobalData::g_myNameStr = usr_list_json_obj["usrName"].toString();
          GlobalData::g_avatarPathStr = usr_list_json_obj["avatarPath"].toString();
        }
      else
        {
          file.resize(0);
          out<<defaultProfile().toJson(QJsonDocument::Compact)<<endl;
        }
    }
  else
    {
      file.resize(0);
      out<<defaultProfile().toJson(QJsonDocument::Compact)<<endl;
    }

  file.flush();
  file.close();
}

void DataManager::loadUsrProfile()
{
  QFile file(usr_list_file_path);
  if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
      return;
    }

  QTextStream in(&file);
  QByteArray in_byte_array = in.readAll().toUtf8();
  file.close();

  QStringList usr_key_str_list;
  QStringList usr_info_str_list;

  ///JSon
  QJsonParseError json_error;
  QJsonDocument read_json_doucment = QJsonDocument::fromJson(in_byte_array, &json_error);
  if(json_error.error == QJsonParseError::NoError)
    {
      if(read_json_doucment.isObject())
        {
          QJsonObject usr_list_json_obj = read_json_doucment.object();
          //get usr_key as a string list
          usr_key_str_list = usr_list_json_obj.keys();
          for(int i = 0; i < usr_key_str_list.count(); i++)
            {
              QJsonObject temp_usr_profile_json_obj;
              //for each usr_key
              QString temp_usr_key_str = usr_key_str_list[i];
              temp_usr_profile_json_obj = usr_list_json_obj[temp_usr_key_str].toObject();
              ///usrKey<<usrName<<ipAddr
              qDebug()<<usr_key_str_list[i];
              usr_info_str_list << temp_usr_profile_json_obj["usrKey"].toString()
                  << temp_usr_profile_json_obj["usrName"].toString()
                  << temp_usr_profile_json_obj["ipAddr"].toString()
                  << temp_usr_profile_json_obj["avatarPath"].toString();


              emit usrProfileLoaded(usr_info_str_list);
              usr_info_str_list.clear();

              //check dir
              checkDir(usr_path+temp_usr_key_str);
            }

        }
    }
  else
    {
      qDebug()<<"Contact parse failed, is file empty?******";
      return;
    }

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
void DataManager::readMessage(QString usrKey)
{

  qDebug()<<usrKey;


}

void DataManager::saveMessage(QStringList messageStrList)
{

}
