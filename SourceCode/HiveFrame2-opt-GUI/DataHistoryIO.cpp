#include "DataHistoryIO.h"

DataHistoryIO::DataHistoryIO(QString usrKey, QObject *parent) : QObject(parent)
{
  usr_key = usrKey;
  history_path = usr_path+usr_key;

  DataManager::checkDir(history_path);

  ///Qt 5.5.0 bug here! put it back to the class def as soon a possible!
  QList<QJsonObject> history_var_list;

  QDir history_dir(history_path);
  int history_file_num = 0;
  foreach (QFileInfo temp_file_info, history_dir.entryInfoList())
    {
      if(temp_file_info.isFile())
        {
          qDebug()<<"file"<<temp_file_info.absoluteFilePath();

          QFile file(temp_file_info.absoluteFilePath());
          if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
            {
              return;
            }

          QTextStream in(&file);
          QByteArray in_byte_array = in.readAll().toUtf8();

          QJsonParseError json_error;
          QJsonDocument json_document = QJsonDocument::fromJson(in_byte_array, &json_error);
          if(json_error.error == QJsonParseError::NoError)
            {
              if(json_document.isObject())
                {
                  history_var_list << json_document.object();
                }
              history_file_num ++;
            }
        }
    }

  if(history_file_num == 0)
    {
      makeHistoryFile(1);
    }

  this->setParent(parent);
}

DataHistoryIO::~DataHistoryIO()
{
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
  history_info_json_obj.insert("date", GlobalData::g_currentTime());

  QJsonDocument history_info_json_doc;
  history_info_json_doc.setObject(history_info_json_obj);

  out<<history_info_json_doc.toJson();

  file.flush();
  file.close();
}


