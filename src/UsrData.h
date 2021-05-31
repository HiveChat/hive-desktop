#ifndef DATAUSER_H
#define DATAUSER_H

#include "GlobalType.h"
#include "Log.h"
#include "Message.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QStandardPaths>

#include <QDebug>
#include <QThread>


class MessageHelper;
//class

class UsrData;

class UsrData
{
public:

  explicit UsrData(QString *myKey, const UsrProfile &getProfile);
  explicit UsrData();
  ~UsrData();

  void addUnreadMessage(const Message::TextMessage &message);
  void setUsrProfile(const UsrProfile &getProfile);

  QJsonArray* flipLatest();
  QJsonArray* flipUp();
  QJsonArray* flipDown();
  QList<QJsonObject>* retrieveUnreadMessage();

  bool isOnline();
  QString getKey() {return profile.key;}
  QString getName() {return profile.name;}
  QString getAvatar() {return profile.avatar;}
  QString getIp() {return profile.ip;}
  UsrProfile* getProfile() {return &profile;}
  int getCurrentHistoryBundleIndex() {return current_history_bundle_index;}
  int getUnreadMessageNumber() {return unread_message_list.count();}

private:

#ifndef Q_OS_WIN
  const QString app_data_local_path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
#else
  const QString app_data_local_path = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
#endif

  const QString usr_path = app_data_local_path + "/usr/";
  UsrProfile profile;
  QString history_path;
  QString *my_key;

  const int max_bundle_capacity = 100;
  int current_history_bundle_index;
  int latest_history_bundle_index;
  QList<QJsonObject> unread_message_list;
  QList<QJsonObject> unread_message_buffer_list;
  QList<QJsonArray> history_bundle_list;//Boxes of canned patato chips
  QJsonArray latest_history_json_array;//A stack of patato chips

  inline bool checkDir(const QString &directory);
  inline QJsonObject getMessageJsonObject(const Message::TextMessage &msg);

  inline void readHistoryBundle();
  inline void makeHistoryBundle(const int &index);
  inline void saveHistoryBundle();
  inline void recordMessage(const Message::TextMessage &msg);
  inline void recordMessage(const QJsonObject &msg);
  inline void recordMessage(const QList<QJsonObject> &msgs);

};

#endif // DATAUSER_H
