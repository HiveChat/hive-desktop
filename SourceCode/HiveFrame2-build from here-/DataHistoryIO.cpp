#include "DataHistoryIO.h"

DataHistoryIO::DataHistoryIO(const QString &usrKey, QObject *parent) : QObject(parent)
{
  usr_key = usrKey;
  history_path = usr_path+usr_key;

  ThreadData::checkDir(history_path);

  for(int i = 1;;i++)
    {
      QString tmp_file_path = QString(history_path+"/%1.json").arg(i);
      QFile file(tmp_file_path);
      if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
          if(i == 1)
            {
              current_active_index = 1;
              makeHistoryFile(current_active_index);
            }
          break;
        }

      QTextStream in(&file);
      QByteArray in_byte_array = in.readAll().toUtf8();
      file.flush();
      file.close();

      QJsonParseError json_error;
      QJsonDocument json_document = QJsonDocument::fromJson(in_byte_array, &json_error);
      if(json_error.error == QJsonParseError::NoError && json_document.isObject())
        {
          QJsonObject temp_history_json_obj;
          temp_history_json_obj = json_document.object();

          if(temp_history_json_obj.value("full").toBool())  //if full
            {
              full_history_list.append(temp_history_json_obj);
            }
          else
            {
              active_history_json_array = temp_history_json_obj.value("history").toArray();
              current_active_index = i;
              break;
            }
        }
    }///for
}

DataHistoryIO::~DataHistoryIO()
{
  saveMessage();
}

QJsonArray DataHistoryIO::readMessage(int index)
{
  return active_history_json_array;
}

void DataHistoryIO::wirteMessage(MessageStruct messageStruct, bool fromMe)
{
    if(active_history_json_array.count() == 100)
      {
        saveMessage();
      }
    QJsonObject message_json_obj;
    message_json_obj.insert("message", messageStruct.message_str);
    message_json_obj.insert("fromMe", fromMe);
    message_json_obj.insert("time", messageStruct.time_str);

    active_history_json_array.append(message_json_obj);

    saveMessage();
}

void DataHistoryIO::makeHistoryFile(int num)
{
  QString make_file_path = QString(history_path+"/%0.json").arg(QString::number(num));
  qDebug()<<"#DataHistoryIO::makeHistoryFile(int num): Make new history:";
  qDebug()<<make_file_path;

  QFile file(make_file_path);
  if(!file.open(QIODevice::ReadWrite | QIODevice::Text))
    {
      return;
    }
  QTextStream out(&file);

  QJsonObject history_info_json_obj;
  history_info_json_obj.insert("full", false);

  QJsonDocument history_info_json_doc;
  history_info_json_doc.setObject(history_info_json_obj);
  out<<history_info_json_doc.toJson();

  file.flush();
  file.close();
}

void DataHistoryIO::saveMessage()
{
  //write to the file
  QString file_path = QString(history_path+"/%1.json").arg(current_active_index);
  QFile file(file_path);
  if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
      return;
    }
  QTextStream out(&file);

  ///max num of messages allowed in each file.
  if(active_history_json_array.count() < 100)
    {
      active_history_json_obj.insert("full", false);
      active_history_json_obj.insert("history", active_history_json_array);

      QJsonDocument active_history_json_doc;
      active_history_json_doc.setObject(active_history_json_obj);
      out << active_history_json_doc.toJson();
    }
  else
    {
      active_history_json_obj.insert("full", true);
      active_history_json_obj.insert("history", active_history_json_array);

      full_history_list.append(active_history_json_obj);

      QJsonDocument active_history_json_doc;
      active_history_json_doc.setObject(active_history_json_obj);

      out << active_history_json_doc.toJson();

      //clear active things
      active_history_json_obj.remove("full");
      active_history_json_obj.remove("history");

      while(!active_history_json_array.isEmpty())
        {
          active_history_json_array.removeLast();
        }

      current_active_index ++;
      makeHistoryFile(current_active_index);
    }

  file.flush();
  file.close();
}

int DataHistoryIO::currentActiveIndex()
{
  return current_active_index;
}


