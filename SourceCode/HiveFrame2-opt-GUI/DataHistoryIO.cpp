#include "DataHistoryIO.h"

DataHistoryIO::DataHistoryIO(QString usrKey, QObject *parent) : QObject(parent)
{
  usr_key = usrKey;
  history_path = usr_path+usr_key;

  DataManager::checkDir(history_path);

  ///Qt 5.5.0 bug here! put it back to the class def as soon a possible!


  for(int i = 1;; i++)
    {
      QString tmp_file_path = QString(history_path+"/%1.json").arg(i);
      QFile file(tmp_file_path);
      if(file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
          QTextStream in(&file);
          QByteArray in_byte_array = in.readAll().toUtf8();

          QJsonParseError json_error;
          QJsonDocument json_document = QJsonDocument::fromJson(in_byte_array, &json_error);
          if(json_error.error == QJsonParseError::NoError)
            {
              ///the last check
              if(json_document.isObject())
                {
                  QJsonObject temp_history_json_obj;
                  temp_history_json_obj = json_document.object();
                  if(temp_history_json_obj.value("full").toBool())
                    {
                      ///delete and remain histories
                      temp_history_json_obj.remove("full");
                      temp_history_json_obj.remove("num");
                      full_history_list.append(temp_history_json_obj);
                    }
                  else
                    {
                      ///delete and remain histories
                      temp_history_json_obj.remove("full");
                      temp_history_json_obj.remove("num");
                      active_history_json_obj = temp_history_json_obj;
                    }
                }///the last check
            }
        }
      else
        {
          break;
        }
    }

//  QDir history_dir(history_path);
//  int history_file_num = 0;
//  foreach (QFileInfo temp_file_info, history_dir.entryInfoList())
//    {
//      if(temp_file_info.isFile())
//        {
//          qDebug()<<"file"<<temp_file_info.absoluteFilePath();

//          QFile file(temp_file_info.absoluteFilePath());
//          if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
//            {
//              continue;
//            }

//          QTextStream in(&file);
//          QByteArray in_byte_array = in.readAll().toUtf8();

//          QJsonParseError json_error;
//          QJsonDocument json_document = QJsonDocument::fromJson(in_byte_array, &json_error);
//          if(json_error.error == QJsonParseError::NoError)
//            {
//              if(json_document.isObject())
//                {
//                  QJsonObject temp_history_json_obj;
//                  temp_history_json_obj = json_document.object();
//                  temp_history_json_obj.value("num").toInt();
//                  temp_history_json_obj.value("full").toBool();
//                }
//              history_file_num ++;
//            }
//        }
//    }

  if(full_history_list.isEmpty() && active_history_json_obj.isEmpty())
    {
      makeHistoryFile(1);
    }

  this->setParent(parent);
}

DataHistoryIO::~DataHistoryIO()
{

}

void DataHistoryIO::readMessage(int index)
{


}

void DataHistoryIO::wirteMessage(QStringList message, bool fromMe)
{
//  message_str_list.append(object_key_str);
//  message_str_list.append(subject_key_str);
//  message_str_list.append(message_str);
//  message_str_list.append(GlobalData::g_currentTime());

  if(message_list.count() < 10)
    {
      QJsonObject message_json_obj;
      message_json_obj.insert("message", message[2]);
      message_json_obj.insert("fromMe", fromMe);
      message_json_obj.insert("time", GlobalData::g_currentTime());

      message_list<<message_json_obj;
    }
  else
    {
      saveMessage();
    }
}

void DataHistoryIO::makeHistoryFile(int num)
{
  QString make_file_path = QString(history_path+"/%0.json").arg(QString::number(num));
  qDebug()<<make_file_path;
  QFile file(make_file_path);

  if(!file.open(QIODevice::ReadWrite | QIODevice::Text))
    {
      return;
    }
  QTextStream out(&file);

  QJsonObject history_info_json_obj;
  history_info_json_obj.insert("full", false);
  history_info_json_obj.insert("num", num);

  QJsonDocument history_info_json_doc;
  history_info_json_doc.setObject(history_info_json_obj);

  out<<history_info_json_doc.toJson();

  file.flush();
  file.close();
}

void DataHistoryIO::saveMessage()
{
  //QList<QJsonObject> message_list;

  foreach (QJsonObject temp_message_json_obj, message_list)
    {
      int current_key_num = active_history_json_obj.count();
      if(current_key_num < 100)
        {
          active_history_json_obj.insert(QString::number(current_key_num), temp_message_json_obj);
        }
      else
        {
          //write full
          //add new file change data in class
          //clear active_history_json_obj
          //clear message_list (right? I'm too tired to think, sorry!)
          //active_history_json_obj.insert(QString::number(current_key_num), temp_message_json_obj);
        }
    }

}


