#ifndef DATAUSER_H
#define DATAUSER_H

#include "GlobalType.h"
#include "Log.h"

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

class UsrData : public QObject
{
  Q_OBJECT
public:

  explicit UsrData(QString *myKey, const UsrProfileStruct &getUsrProfileStruct, QObject *parent = 0);
  explicit UsrData(QObject *parent = 0);
  ~UsrData();

  void addUnreadMessage(const Message::TextMessageStruct &message);
  void setUsrProfileStruct(const UsrProfileStruct &getUsrProfileStruct);

  QJsonArray* flipLatest();
  QJsonArray* flipUp();
  QJsonArray* flipDown();
  QList<QJsonObject>* retrieveUnreadMessage();

  bool isOnline();
  QString getKey() {return usr_profile_struct.key;}
  QString getName() {return usr_profile_struct.name;}
  QString getAvatar() {return usr_profile_struct.avatar;}
  QString getIp() {return usr_profile_struct.ip;}
  UsrProfileStruct* getUsrProfileStruct() {return &usr_profile_struct;}
  int getCurrentHistoryBundleIndex() {return current_history_bundle_index;}
  int getUnreadMessageNumber() {return unread_message_list.count();}

private:

  const QString app_data_local_path = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
  const QString usr_path = app_data_local_path + "/usr/";
  UsrProfileStruct usr_profile_struct;
  QString history_path;
  QString *my_key;

  const int max_bundle_capacity = 100;
  int current_history_bundle_index;
  int latest_history_bundle_index;
  QList<QJsonObject> unread_message_list;
  QList<QJsonObject> unread_message_buffer_list;
  QList<QJsonArray> history_bundle_list;//Boxes of canned patato chips
  QJsonArray latest_history_json_array;//A stack of patato chips

  //Funciton
  inline bool checkDir(const QString &directory);
  inline QJsonObject getMessageJsonObject(const Message::TextMessageStruct &messageStruct);

  inline void readHistoryBundle();
  inline void makeHistoryBundle(const int &index);
  inline void saveHistoryBundle();
  inline void recordMessage(const Message::TextMessageStruct &messageStruct);
  inline void recordMessage(const QJsonObject &messageJsonObject);
  inline void recordMessage(const QList<QJsonObject> &messageJsonObjectList);

};

#endif // DATAUSER_H
