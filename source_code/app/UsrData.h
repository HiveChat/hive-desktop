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

  explicit UsrData(QString *myKey, const UsrProfile &getUsrProfile);
  explicit UsrData();
  ~UsrData();

  void addUnreadMessage(const Message::TextMessage &message);
  void setUsrProfileStruct(const UsrProfile &getUsrProfile);

  QJsonArray* flipLatest();
  QJsonArray* flipUp();
  QJsonArray* flipDown();
  QList<QJsonObject>* retrieveUnreadMessage();

  bool isOnline();
  QString getKey() {return usr_profile_struct.key;}
  QString getName() {return usr_profile_struct.name;}
  QString getAvatar() {return usr_profile_struct.avatar;}
  QString getIp() {return usr_profile_struct.ip;}
  UsrProfile* getUsrProfile() {return &usr_profile_struct;}
  int getCurrentHistoryBundleIndex() {return current_history_bundle_index;}
  int getUnreadMessageNumber() {return unread_message_list.count();}

private:

#ifndef Q_OS_WIN
  const QString app_data_local_path = QStandardPaths::writableLocation(QStandardPaths::DataLocation);
#else
  const QString app_data_local_path = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
#endif

  const QString usr_path = app_data_local_path + "/usr/";
  UsrProfile usr_profile_struct;
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
  inline QJsonObject getMessageJsonObject(const Message::TextMessage &messageStruct);

  inline void readHistoryBundle();
  inline void makeHistoryBundle(const int &index);
  inline void saveHistoryBundle();
  inline void recordMessage(const Message::TextMessage &messageStruct);
  inline void recordMessage(const QJsonObject &messageJsonObject);
  inline void recordMessage(const QList<QJsonObject> &messageJsonObjectList);

};

#endif // DATAUSER_H
