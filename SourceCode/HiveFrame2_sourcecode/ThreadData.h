#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include "GlobalData.h"
#include "UsrData.h"

#include <QThread>
#include <QMutex>
#include <QDebug>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QFileInfo>
#include <QStandardPaths>

#include <QFontDatabase>
#include <QHostInfo>
#include <QTime>

class ThreadData;
class UsrData;


class ThreadData : public QThread
{
  Q_OBJECT

public:
  explicit ThreadData(QObject *parent = 0);
  ~ThreadData();

  void addUsr(UsrProfileStruct *usrProfileStruct);

  void loadUsrList();
  static bool checkDir(const QString &directory);
  static QString appDataLocalPath();
  void TEST_SECTION();



protected:
  void run();

private:

  bool running = true;
  int loop_count = 1;
  void checkSettings();
  void refreshGui();

  Settings::SettingStruct written_settings_struct;

  QJsonDocument makeUsrProfile();
  QJsonObject makeUsrProfile(UsrProfileStruct &usrProfileStruct);
  QJsonDocument makeUsrList(QList<QJsonObject> &usr_profile_list);

  void makeUsrKey();
  void initVariable();
  void initPalette();
  void checkFiles();
  void loadDefaultGlobalData();
  void loadMyProfile();
  void loadFonts();

  void deleteUsr(const QStringList usrInfoStrList);

  const QString app_data_local_path = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
  const QString usr_path = app_data_local_path + "/usr/";
  const QString log_path = app_data_local_path + "/log/";

  const QString usr_list_file_path = app_data_local_path + "/usr_list.json";
  const QString my_profile_file_path = app_data_local_path + "/my_profile.json";

  //data map
  QMap<QString, UsrProfileStruct> local_usr_profile_map;
  QMap<QString, UsrProfileStruct> online_usr_profile_map;

  //config map
  QMap<QString, QColor*> myColorConfigJsonMap;
  QMap<QString, QString*> myProfileConfigJsonMap;

public slots:
  void onUsrEntered(UsrProfileStruct *usrProfileStruct);
  void onUsrLeft(QString *usrKey);
  void onMessageCome(MessageStruct *messageStruct, bool fromMe);

  void writeCurrentConfig();


signals:
  void refreshGuiInfo();
  void usrProfileLoaded(UsrData *userData);
  void usrProfileChanged(UsrData *userData);
  void messageLoaded(MessageStruct messageStrList, bool fromMe);


};

#endif // DATAMANAGER_H
