#include "UsrData.h"


UsrData::UsrData(QString *myKey, const UsrProfileStruct &usrProfileStruct, QObject *parent) : QObject(parent)
{
  my_key = myKey;
  this->setUsrProfileStruct(usrProfileStruct);
  history_path = usr_path + usr_profile_struct.key;
  this->checkDir(history_path);
  this->readHistoryBundle();

}

UsrData::UsrData(QObject *parent) : QObject(parent)
{
}

UsrData::~UsrData()
{
  recordMessage(unread_message_list);
}

void UsrData::addUnreadMessage(const Message::TextMessageStruct &message)
{
  unread_message_list.append(getMessageJsonObject(message));
}

void UsrData::setUsrProfileStruct(const UsrProfileStruct &usrProfileStruct)
{
  usr_profile_struct = usrProfileStruct;
}

QList<QJsonObject> *UsrData::retrieveUnreadMessage()
{
  unread_message_buffer_list = unread_message_list;
  recordMessage(unread_message_list);
  unread_message_list.clear();
  return &unread_message_buffer_list;
}


QJsonArray* UsrData::flipLatest()
{
  current_history_bundle_index = latest_history_bundle_index;
  return &latest_history_json_array;
}

QJsonArray* UsrData::flipUp()
{
  current_history_bundle_index --;
  if(current_history_bundle_index > 0)
    {
      return &history_bundle_list[current_history_bundle_index];
    }
  else
    {
      return NULL;
    }
}

QJsonArray* UsrData::flipDown()
{
  current_history_bundle_index ++;
  if(current_history_bundle_index == latest_history_bundle_index)
    {
      return &latest_history_json_array;
    }
  else if(current_history_bundle_index < latest_history_bundle_index)
    {
      return &history_bundle_list[current_history_bundle_index];
    }
  else
    {
      return NULL;
    }
}


bool UsrData::checkDir(const QString &directory)
{
  QDir dir(directory);
  if(!dir.exists())
    {
      if(!dir.mkdir(directory))
        {
          return false;
        }
    }
  return true;
}

void UsrData::readHistoryBundle()
{
  for(int index = 1; ; index ++)
    {
      QString tmp_file_path = QString(history_path+"/%1.json").arg(index);
      QFile file(tmp_file_path);
      if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
          if(index == 1)
            {
              latest_history_bundle_index = 1;
              makeHistoryBundle(latest_history_bundle_index);
            }
          break;
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
              //put full history_bundle to the list
              history_bundle_list.append( temp_history_json_obj.value("history").toArray());
            }
          else
            {
              latest_history_json_array = temp_history_json_obj.value("history").toArray();
              latest_history_bundle_index = index;
              break;
            }
        }
    }
  current_history_bundle_index = latest_history_bundle_index;
}

void UsrData::refreshUsrProfile(const UsrProfileStruct &usrProfileStruct)
{
  usr_profile_struct = usrProfileStruct;
}

QJsonObject UsrData::getMessageJsonObject(const Message::TextMessageStruct &messageStruct)
{
  bool fromMe = (messageStruct.sender == my_key);
  QJsonObject json_object;
  json_object.insert("fromMe", fromMe);
  json_object.insert("message", messageStruct.message);
  json_object.insert("time", messageStruct.time);

  return json_object;
}

void UsrData::makeHistoryBundle(int num)
{
  QString file_path = QString(history_path+"/%0.json").arg(QString::number(num));
  qDebug()<<"#UsrData::makeHistoryFile(int num): Make new history:";
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

void UsrData::saveHistoryBundle()
{
//  auto lambda = [&]()
//    {
      QString file_path = QString(history_path+"/%1.json").arg(current_history_bundle_index);
      QFile file(file_path);
      if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
          return;
        }
      QTextStream out(&file);

      ///max num of messages allowed in each file.
      QJsonObject history_bundle_json_obj;
      if(latest_history_json_array.count() < max_bundle_capacity)
        {
          history_bundle_json_obj.insert("full", false);
          history_bundle_json_obj.insert("history", latest_history_json_array);

          QJsonDocument active_history_json_doc;
          active_history_json_doc.setObject(history_bundle_json_obj);
          out << active_history_json_doc.toJson();
        }
      else
        {
          history_bundle_json_obj.insert("full", true);
          history_bundle_json_obj.insert("history", latest_history_json_array);

          history_bundle_list.append(history_bundle_json_obj.value("history").toArray());

          QJsonDocument active_history_json_doc;
          active_history_json_doc.setObject(history_bundle_json_obj);
          out << active_history_json_doc.toJson();

    //      for(int i = 0; i < current_history_json_array.count(); i++)
    //        {
    //          current_history_json_array.removeFirst();
    //        }
          latest_history_json_array = QJsonArray();

          current_history_bundle_index ++;
          makeHistoryBundle(current_history_bundle_index);
        }

      file.flush();
      file.close();
//    };

//  QtConcurrent::run(lambda);
}

void UsrData::recordMessage(const Message::TextMessageStruct &messageStruct, bool fromMe)
{
  if(latest_history_json_array.count() >= max_bundle_capacity)
    {
      saveHistoryBundle();
    }
  QJsonObject message_json_obj;
  message_json_obj.insert("message", messageStruct.message);
  message_json_obj.insert("fromMe", fromMe);
  message_json_obj.insert("time", messageStruct.time);

  latest_history_json_array.append(message_json_obj);

  saveHistoryBundle();
}

void UsrData::recordMessage(const QJsonObject &messageJsonObject)
{
  if(latest_history_json_array.count() >= max_bundle_capacity)
    {
      saveHistoryBundle();
    }
  latest_history_json_array.append(messageJsonObject);

  saveHistoryBundle();
}

void UsrData::recordMessage(const QList<QJsonObject> &messageJsonObjectList)
{
  foreach (QJsonObject json_obj, messageJsonObjectList)
    {
      if(latest_history_json_array.count() >= max_bundle_capacity)
        {
          saveHistoryBundle();
        }
      latest_history_json_array.append(json_obj);
    }
  saveHistoryBundle();
}






