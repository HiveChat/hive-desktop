#include "DataHistoryIO.h"

DataHistoryIO::DataHistoryIO(QString usrKey, QObject *parent) : QObject(parent)
{
  usr_key = usrKey;
  history_path = usr_path+usr_key;

  DataManager::checkDir(history_path);

  ///Qt 5.5.0 bug here! put it back to the class def as soon a possible!

  //debug
  int debug_active_mun = 0;
  //-debug

  for(int i = 1;;i++)
    {
      QString tmp_file_path = QString(history_path+"/%1.json").arg(i);
      QFile file(tmp_file_path);
      if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
          break;
        }

      QTextStream in(&file);
      QByteArray in_byte_array = in.readAll().toUtf8();
      file.flush();
      file.close();

      QJsonParseError json_error;
      QJsonDocument json_document = QJsonDocument::fromJson(in_byte_array, &json_error);
      if(json_error.error == QJsonParseError::NoError)
        {
          ///the last check
          if(json_document.isObject())
            {
              QJsonObject temp_history_json_obj;
              temp_history_json_obj = json_document.object();
              ///if full
              if(temp_history_json_obj.value("full").toBool())
                {
                  debug_active_mun ++;
                  full_history_list.append(temp_history_json_obj);
                }
              else
                {
                  //debug
                  debug_active_mun ++;
                  //-debug

                  active_history_json_array = temp_history_json_obj["history"].toArray();
                      //= temp_history_json_obj;
                  current_active_index = i;
                }
            }///the last check if
        }
    }///for

  if(debug_active_mun == 0)
    {
      qDebug()<<"\nno history\n";
      qDebug()<<"\nmake new history \n";
      current_active_index = 1;
      makeHistoryFile(current_active_index);
    }

  this->setParent(parent);
}

DataHistoryIO::~DataHistoryIO()
{

}

QJsonArray DataHistoryIO::readMessage(int index)
{
  return active_history_json_array;
}

void DataHistoryIO::wirteMessage(QStringList message, bool fromMe)
{
//  message_str_list.append(object_key_str);
//  message_str_list.append(subject_key_str);
//  message_str_list.append(message_str);
//  message_str_list.append(GlobalData::g_currentTime());

  if(active_history_json_array.count() == 100)
    {
      saveMessage();
    }

  QJsonObject message_json_obj;
  message_json_obj.insert("message", message[2]);
  message_json_obj.insert("fromMe", fromMe);
  message_json_obj.insert("time", message[3]);

  active_history_json_array.append(message_json_obj);

  saveMessage();
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

  if(active_history_json_array.count() < 100)
    {
      active_history_json_obj.insert("full", false);
      active_history_json_obj.insert("history", active_history_json_array);

      QJsonDocument active_history_json_doc;
      active_history_json_doc.setObject(active_history_json_obj);

      out << active_history_json_doc.toJson();
      //qDebug()<<active_history_json_doc.toJson();
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


