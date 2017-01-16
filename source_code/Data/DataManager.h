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

class DataManager : public QObject
{
  Q_OBJECT

public:
  explicit DataManager(QObject *parent = 0);
  ~DataManager();

  void addUsr(UsrProfileStruct *usrProfileStruct);
  void loadUsrList();

private:

  void checkSettings();
  static bool checkDir(const QString &directory);

  QJsonDocument makeUsrProfile();
  QJsonObject makeUsrProfile(UsrProfileStruct &usrProfileStruct);
  QJsonDocument makeUsrList(QList<QJsonObject> &usr_profile_list);
  QJsonDocument makeUpdateJson(const int stable[]);

  void makeUsrKey();
  void initVariable();
  void checkFiles();
  void loadDefaultGlobalData();
  void loadMySettings();
  void loadFonts();
  void loadUpdates();
  void loadTimerTasks();

  void deleteUsr(const QStringList usrInfoStrList);

  const QString app_data_local_path = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
  const QString usr_path = app_data_local_path + "/usr/";
  const QString log_path = app_data_local_path + "/log/";

  const QString contacts_file_path = app_data_local_path + "/contacts.json";
  const QString settings_file_path = app_data_local_path + "/settings.json";
  const QString update_file_path = app_data_local_path + "/update.json";

  //data map
  QHash<QString, UsrProfileStruct> local_usr_profile_hash;

  //config map
  QHash<QString, int*> settings_hash_int;
  QHash<QString, QColor*> settings_hash_qcolor;
  QHash<QString, QString*> settings_hash_qstring;
  QHash<QString, bool*> settings_hash_bool;

public slots:
  void onUsrEntered(const UsrProfileStruct &usrProfileStruct);
  void onUsrLeft(QString *usrKey);
  void onMessageCome(const Message::TextMessageStruct &messageStruct, bool fromMe);
  void onUpdatesAvailable();

private slots:
  void writeCurrentConfig();


signals:
  void updatesAvailable();
  void usrProfileLoaded(UsrData *userData);
  void usrProfileChanged(UsrData *userData);
  void messageLoaded(Message::TextMessageStruct messageStrList, bool fromMe);


};

#endif // DATAMANAGER_H
