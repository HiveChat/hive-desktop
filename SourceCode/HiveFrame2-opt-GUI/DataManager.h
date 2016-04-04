#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include "GlobalData.h"

#include <QDebug>
#include <QObject>
#include <QHostInfo>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QFileInfo>
#include <QStandardPaths>
#include <QFontDatabase>

#include <QTime>





class DataManager : public QObject
{
  Q_OBJECT

public:
  explicit DataManager(QObject *parent = 0);

  void addUsr(UsrProfileStruct *usrProfileStruct);

  void loadUsrProfile();
  static bool checkDir(QString dir);
  static QString appDataLocalPath();
  void TEST_SECTION();

private:

  QJsonDocument defaultProfile();
  void makeUsrKey();

  void checkData();
  void loadDefaultGlobalData();
  void loadMyProfile();
  void loadFonts();

  void deleteUsr(QStringList usrInfoStrList);

  const QString app_data_local_path = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
  const QString usr_path = app_data_local_path + "/usr/";
  const QString log_path = app_data_local_path + "/log/";

  const QString usr_list_file_path = app_data_local_path + "/usr_list.json";
  const QString my_profile_file_path = app_data_local_path + "/my_profile.json";

  QMap<QString, QColor*> myColorConfigJsonMap;
  QMap<QString, QString*> myProfileConfigJsonMap;

public slots:
  void writeCurrentConfig();


signals:
  void usrProfileLoaded(UsrProfileStruct *usrProfileStruct);
  void messageLoaded(QStringList messageStrList);



};

#endif // DATAMANAGER_H
