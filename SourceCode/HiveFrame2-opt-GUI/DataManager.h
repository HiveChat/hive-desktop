#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include "GlobalData.h"

#include <QDebug>
#include <QObject>
#include <QHostInfo>

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

  void checkData();
  void loadMyProfile();
  void loadUsrProfile();

  void addUsr(QStringList usrInfoStrList);
  void deleteUsr(QStringList usrInfoStrList);

  //void addChatHistory();
  void TEST_SECTION();

private:
  bool checkDir(QString dir);
  QJsonDocument defaultProfile();
  void makeUsrKey();

  const QString app_data_local_path = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
  const QString usr_path = app_data_local_path+ "/usr/";
  const QString log_path = app_data_local_path + "/log/";

  const QString usr_list_file_path = app_data_local_path + "/usr_list.json";
  const QString my_profile_file_path = app_data_local_path + "/my_profile.json";



  ///usrData
  const char alphabet_char[64] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_";

  //QStringList usr_info_str_list;

signals:
  void usrProfileLoaded(QStringList usrInfoStrList);
  //void onFirstLaunch();
  void messageLoaded(QStringList messageStrList);


public slots:
  void readMessage(QString usrKey);
  void saveMessage(QStringList messageStrList);

};

#endif // DATAMANAGER_H
