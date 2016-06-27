#include "UserData.h"

UserData::UserData(const UsrProfileStruct &usr_profile_struct, QObject *parent) : QObject(parent)
{
  usr_key = usr_profile_struct.key_str;
  history_path = usr_path+usr_key;

  ThreadData::checkDir(history_path);
  readHistoryBundle();

}

UserData::~UserData()
{
  saveHistoryBundle();
}

void UserData::readHistoryBundle()
{
//  int index = 1;
  for(int fail = 0, index = 1; fail <= 3; )
    {
      QString tmp_file_path = QString(history_path+"/%1.json").arg(index);
      QFile file(tmp_file_path);
      if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
          if(index == 1)
            {
              current_history_bundle_index = 1;
              makeHistoryBundle(current_history_bundle_index);
              break;
            }
          else
            {
              fail ++;
            }
        }

      QTextStream in(&file);
      QByteArray in_byte_array = in.readAll().toUtf8();
      file.flush();
      file.close();
      ///finish disk operation.

      QJsonParseError json_error;
      QJsonDocument json_document = QJsonDocument::fromJson(in_byte_array, &json_error);
      if(json_error.error == QJsonParseError::NoError && json_document.isObject())
        {
          QJsonObject temp_history_json_obj;
          temp_history_json_obj = json_document.object();

          if(temp_history_json_obj.value("full").toBool())
            {
              history_bundle_list.append(temp_history_json_obj);
            }
          else
            {
              current_history_json_array = temp_history_json_obj.value("history").toArray();
              current_history_bundle_index = index;
              break;
            }
        }
    }
}

void UserData::refreshUsrProfile(const UsrProfileStruct &usrProfileStruct)
{
  usr_profile_struct = usrProfileStruct;
}

void UserData::makeHistoryBundle(int num)
{
  QString file_path = QString(history_path+"/%0.json").arg(QString::number(num));
  qDebug()<<"#DataHistoryIO::makeHistoryFile(int num): Make new history:";
  qDebug()<<file_path;

  QFile file(file_path);
  if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
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

void UserData::saveHistoryBundle()
{
  auto lambda = [this]()
    {
      QString file_path = QString(history_path+"/%1.json").arg(current_history_bundle_index);
      QFile file(file_path);
      if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
          return;
        }
      QTextStream out(&file);

      ///max num of messages allowed in each file.
      QJsonObject history_bundle_json_obj;
      if(current_history_json_array.count() < max_bundle_capacity)
        {
          history_bundle_json_obj.insert("full", false);
          history_bundle_json_obj.insert("history", current_history_json_array);

          QJsonDocument active_history_json_doc;
          active_history_json_doc.setObject(history_bundle_json_obj);
          out << active_history_json_doc.toJson();
        }
      else
        {
          history_bundle_json_obj.insert("full", true);
          history_bundle_json_obj.insert("history", current_history_json_array);

          history_bundle_list.append(history_bundle_json_obj);

          QJsonDocument active_history_json_doc;
          active_history_json_doc.setObject(history_bundle_json_obj);
          out << active_history_json_doc.toJson();

    //      for(int i = 0; i < current_history_json_array.count(); i++)
    //        {
    //          current_history_json_array.removeFirst();
    //        }
          current_history_json_array = QJsonArray();

          current_history_bundle_index ++;
          makeHistoryBundle(current_history_bundle_index);
        }

      file.flush();
      file.close();
    };

  QtConcurrent::run(lambda);
}

void UserData::recordMessage(MessageStruct messageStruct, bool fromMe)
{
  if(current_history_json_array.count() >= max_bundle_capacity)
    {
      saveHistoryBundle();
    }
  QJsonObject message_json_obj;
  message_json_obj.insert("message", messageStruct.message_str);
  message_json_obj.insert("fromMe", fromMe);
  message_json_obj.insert("time", messageStruct.time_str);

  current_history_json_array.append(message_json_obj);

  saveHistoryBundle();
}






