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
#include <QThread>

class ThreadData : public QThread
{
  Q_OBJECT

public:
  explicit ThreadData(QObject *parent = 0);
  ~ThreadData();

  void addUsr(UsrProfileStruct *usrProfileStruct);

  void loadUsrList();
  static bool checkDir(const QString dir);
  static QString appDataLocalPath();
  void TEST_SECTION();

protected:
  void run();

private:

  bool running = true;
  void checkSettings();

  SettingStruct written_settings_struct;
  QColor b_mChatBubbleColorI;
  QColor b_mChatBubbleColorO;
  QString b_myNameStr;
  QString b_avatarPathStr;



  QJsonDocument defaultProfile();
  void makeUsrKey();

  void initVariable();
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
  QMap<QString, UsrProfileStruct> localUsrProfileMap;
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
  void usrProfileLoaded(UsrProfileStruct *usrProfileStruct);
  void usrProfileChanged(UsrProfileStruct *usrProfileStruct);
  void messageLoaded(QStringList messageStrList);


};

#endif // DATAMANAGER_H
