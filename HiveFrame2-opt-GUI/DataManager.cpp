#include "DataManager.h"

DataManager::DataManager(QObject *parent) : QObject(parent)
{
  checkDir(app_data_local_path);
    checkDir(usr_path);
    checkDir(usr_path);


  this->setParent(parent);
}

void DataManager::addUsr(QString usrName, QString ipAddr, QString macAddr)
{
  ///JSon

  QJsonObject usr_list_json_obj;
  usr_list_json_obj.insert("usrName", usrName);
  usr_list_json_obj.insert("ipAddr", ipAddr);
  usr_list_json_obj.insert("macAddr", macAddr);

  QJsonDocument usr_list_json_doc;
  usr_list_json_doc.setObject(usr_list_json_obj);

  QByteArray byte_array = usr_list_json_doc.toJson(QJsonDocument::Compact);

  ///file
  QFile file(usr_list_file_path);
  qDebug()<<byte_array;
  if(!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
  {
    return;
  }

  QTextStream out(&file);

  out<<usr_list_json_doc.toJson(QJsonDocument::Compact)<<endl;
  file.close();
  file.flush();

}

void DataManager::deleteUsr(QString usrName, QString ipAddr, QString macAddr)
{
  QFile file(usr_list_file_path);

  if(!file.open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Append))
    {
      qDebug()<<"usr_list_file_path NOT OPENED";
      return;
    }
  QTextStream in(&file);
  QTextStream out(&file);

  /*QJsonArray temp_json_array;
  QStringList temp_str_list;
  while(!file.atEnd())
    {
      temp_str_list.append(in.readLine());

      temp_json_array = QJsonArray::fromStringList(temp_str_list);
      if(temp_json_array.contains(usrName)
         &&temp_json_array.contains(ipAddr)
         &&temp_json_array.contains(macAddr))
        {
          continue;
        }

      out<<temp_str_list.first()<<endl;
    }*/

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
