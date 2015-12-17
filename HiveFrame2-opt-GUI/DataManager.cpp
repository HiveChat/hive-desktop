#include "DataManager.h"
#include "QVariantMap"

DataManager::DataManager(QObject *parent) : QObject(parent)
{
  checkDir(app_data_local_path);
    checkDir(usr_path);
    checkDir(usr_path);

    loadUsrForm();

  this->setParent(parent);
}

void DataManager::addUsr(QString usrName, QString ipAddr, QString macAddr)
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
          if(!usr_list_json_obj.contains(macAddr))
            {
              QJsonObject usr_info_json_obj;
              usr_info_json_obj.insert("usrName", usrName);
              usr_info_json_obj.insert("ipAddr", ipAddr);
              usr_info_json_obj.insert("macAddr", macAddr);

              usr_list_json_obj.insert(macAddr, usr_info_json_obj);

              QJsonDocument write_json_doucment;
              write_json_doucment.setObject(usr_list_json_obj);

              out<<write_json_doucment.toJson(QJsonDocument::Compact)<<endl;
            }
        }

    }
  else
    {
      QJsonObject usr_info_json_obj;
      usr_info_json_obj.insert("usrName", usrName);
      usr_info_json_obj.insert("ipAddr", ipAddr);
      usr_info_json_obj.insert("macAddr", macAddr);

      QJsonObject usr_list_json_obj;
      usr_list_json_obj.insert(macAddr, usr_info_json_obj);

      QJsonDocument write_json_doucment;
      write_json_doucment.setObject(usr_list_json_obj);

      out<<write_json_doucment.toJson(QJsonDocument::Compact)<<endl;
      qDebug()<<write_json_doucment.toJson(QJsonDocument::Compact);

    }


  file.close();
  file.flush();



}

void DataManager::deleteUsr(QString usrName, QString ipAddr, QString macAddr)
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
          usr_list_json_obj.erase(usr_list_json_obj.find(macAddr));

          QJsonDocument write_json_doucment;
          write_json_doucment.setObject(usr_list_json_obj);
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

void DataManager::loadUsrForm()
{
  QFile file(usr_list_file_path);
  if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
  {
    return;
  }

  QTextStream in(&file);

  QByteArray in_byte_array = in.readAll().toUtf8();

  QList<QStringList> usr_form;
  QStringList temp_usr_info_str_list;


  ///JSon
  QJsonParseError json_error;
  QJsonDocument read_json_doucment = QJsonDocument::fromJson(in_byte_array, &json_error);
  if(json_error.error == QJsonParseError::NoError)
    {
      if(read_json_doucment.isObject())
        {
          QJsonObject usr_list_json_obj = read_json_doucment.object();
          QVariantMap usr_list_variant_map = usr_list_json_obj.toVariantMap();
          QJsonObject temp_usr_info_json_obj;

          for(int i = 0; i < usr_list_variant_map.count(); i++)
            {

              temp_usr_info_json_obj = usr_list_variant_map.first().toJsonObject();
              usr_list_variant_map.remove(usr_list_variant_map.firstKey());

              qDebug()<<temp_usr_info_json_obj;
              temp_usr_info_str_list << temp_usr_info_json_obj["macAddr"].toString();
              temp_usr_info_str_list << temp_usr_info_json_obj["ipAddr"].toString();
              temp_usr_info_str_list << temp_usr_info_json_obj["usrName"].toString();
              temp_usr_info_str_list << temp_usr_info_json_obj["avatarNum"].toString();

              usr_form << temp_usr_info_str_list;
              temp_usr_info_str_list.clear();

            }


          QJsonDocument write_json_doucment;
          write_json_doucment.setObject(usr_list_json_obj);
          //out<<write_json_doucment.toJson(QJsonDocument::Compact)<<endl;
          qDebug()<<write_json_doucment.toJson(QJsonDocument::Compact);

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
