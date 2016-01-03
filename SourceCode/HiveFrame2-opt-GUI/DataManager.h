#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QDebug>
#include <QObject>

#include <QJsonDocument>
#include <QJsonObject>

#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QStandardPaths>

#include <QTime>

class DataManager : public QObject
{
  Q_OBJECT

public:
  explicit DataManager(QObject *parent = 0);


  void addUsr(QStringList usrInfoStrList);
  void deleteUsr(QStringList usrInfoStrList);
  void loadUsrProfile();

  //void addChatHistory();

signals:
  void onUsrProfileLoaded(QStringList usrInfoStrList);
  void onFirstLaunch();

private:  
  bool checkDir(QString dir);
  QStringList parseMyProfile(QJsonObject my_profile_json_obj);
  QJsonObject makeMyProfile(QStringList my_profile_str_list);
  QString makeUsrKey();

  QString app_data_local_path = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
  QString usr_path = app_data_local_path+ "/usr/";
  QString log_path = app_data_local_path + "/log/";

  QString usr_list_file_path = app_data_local_path + "/usr_list.json";
  QString my_profile_file_path = app_data_local_path + "/my_profile.json";



  ///usrData
  const char alphabet_char[64] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_";
  QChar usr_key_char[32];
  QString usr_key_str;
  //QStringList usr_info_str_list;

};

#endif // DATAMANAGER_H
