#include "DataManager.h"

DataManager::DataManager(QObject *parent) : QObject(parent)
{
  checkDir(app_data_local_path);
    checkDir(usr_path);
    checkDir(usr_path);


    QStringList usrInfoStrList;

    usrInfoStrList<<"90:00:4E:9A:A4:FD"<<"192.168.1.1"<<"Bob";
    addUsr(usrInfoStrList);
    usrInfoStrList.clear();
    usrInfoStrList<<"90:00:9E:9A:A4:FD"<<"192.168.1.2"<<"Tim";
    addUsr(usrInfoStrList);
    usrInfoStrList.clear();
    usrInfoStrList<<"20:00:9E:9A:A4:FD"<<"192.168.1.3"<<"Rob";
    addUsr(usrInfoStrList);
    usrInfoStrList.clear();
    usrInfoStrList<<"0?:00:9E:9A:A4:FD"<<"192.168.1.4"<<"Paul";
    addUsr(usrInfoStrList);
    usrInfoStrList.clear();
    usrInfoStrList<<"30:00:9E:9A:A4:FD"<<"192.168.1.5"<<"Tom";
    addUsr(usrInfoStrList);
    usrInfoStrList.clear();
    usrInfoStrList<<"40:00:9E:9A:A4:FD"<<"192.168.1.6"<<"Levi";
    addUsr(usrInfoStrList);
    usrInfoStrList.clear();
    usrInfoStrList<<"20:00:9E:9A:A4:FD"<<"192.168.1.7"<<"Peter";
    addUsr(usrInfoStrList);
    usrInfoStrList.clear();
    usrInfoStrList<<"20:00:9E:9A:A4:FD"<<"192.168.1.8"<<"Justin";
    addUsr(usrInfoStrList);
    usrInfoStrList.clear();
    usrInfoStrList<<"30:00:9E:9A:A4:FD"<<"192.168.1.9"<<"Nemo";
    addUsr(usrInfoStrList);
    usrInfoStrList.clear();
    usrInfoStrList<<"40:00:9E:9A:A4:FD"<<"192.168.1.10"<<"Lynn";
    addUsr(usrInfoStrList);
    usrInfoStrList.clear();
    usrInfoStrList<<"90:00:9E:9A:A4:FD"<<"192.168.1.11"<<"Tim";
    deleteUsr(usrInfoStrList);

  this->setParent(parent);
}

void DataManager::addUsr(QStringList usrInfoStrList)
{
  QString mac_addr = usrInfoStrList.at(0);
  QString ip_addr = usrInfoStrList.at(1);
  QString usr_name = usrInfoStrList.at(2);



  ///macAddr<<usrName<<ipAddr
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
          if(!usr_list_json_obj.contains(mac_addr))
            {
              QJsonObject usr_info_json_obj;
              usr_info_json_obj.insert("ipAddr", ip_addr);
              usr_info_json_obj.insert("macAddr", mac_addr);
              usr_info_json_obj.insert("usrName", usr_name);


              usr_list_json_obj.insert(mac_addr, usr_info_json_obj);

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
      usr_info_json_obj.insert("macAddr", mac_addr);
      usr_info_json_obj.insert("usrName", usr_name);


      QJsonObject usr_list_json_obj;
      usr_list_json_obj.insert(mac_addr, usr_info_json_obj);

      QJsonDocument write_json_doucment;
      write_json_doucment.setObject(usr_list_json_obj);

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

  QStringList usr_name_str_list;
  QStringList usr_info_str_list;

  ///JSon
  QJsonParseError json_error;
  QJsonDocument read_json_doucment = QJsonDocument::fromJson(in_byte_array, &json_error);
  if(json_error.error == QJsonParseError::NoError)
    {
      if(read_json_doucment.isObject())
        {
          QJsonObject usr_list_json_obj = read_json_doucment.object();
          usr_name_str_list = usr_list_json_obj.keys();
          for(int i = 0; i <usr_name_str_list.count(); i++)
            {
              QJsonObject temp_usr_profile_json_obj;
              QString temp_usr_name_str = usr_name_str_list[i];
              temp_usr_profile_json_obj = usr_list_json_obj[temp_usr_name_str].toObject();
              ///macAddr<<usrName<<ipAddr
              qDebug()<<usr_name_str_list[i]<<endl;
              usr_info_str_list << temp_usr_profile_json_obj["macAddr"].toString()
                  << temp_usr_profile_json_obj["usrName"].toString()
                  << temp_usr_profile_json_obj["ipAddr"].toString();



              emit onUsrProfileLoaded(usr_info_str_list);
              usr_info_str_list.clear();
            }

        }
    }
  else
    {
      qDebug()<<"Contact parse failed, is file empty?******";

    }

}
/*

{
    "usr_list" : {
      ["Tim", "192.168.1.1", "aa:bb:cc:dd:ee:ff"]
      ["Doge", "192.168.1.2", "aa:bb:cc:dd:ee:ff"]
      ["Bob", "192.168.1.3", "aa:bb:cc:dd:ee:ff"]
      ["Pat", "192.168.1.4", "aa:bb:cc:dd:ee:ff"]
      ["Steve", "192.168.1.5", "aa:bb:cc:dd:ee:ff"]}
  }

  */
