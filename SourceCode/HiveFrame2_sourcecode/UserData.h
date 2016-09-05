#ifndef DATAUSER_H
#define DATAUSER_H

#include <QObject>
#include <QtConcurrent>
#include "GlobalType.h"
//#include "ThreadData.h"//delete?



class UsrData;

class UsrData : public QObject
{
  Q_OBJECT
public:
  explicit UsrData(const UsrProfileStruct &usrProfileStruct, QObject *parent = 0);
  ~UsrData();

  void newMessage(const QJsonObject &message);

  void setUsrProfileStruct(const UsrProfileStruct &usrProfileStruct);

  QList<QJsonObject>* retrieveNewMessage();
  QJsonArray* flipLatest();
  QJsonArray* flipUp();
  QJsonArray* flipDown();

  UsrProfileStruct* usrProfileStruct(){return &usr_profile_struct;}
  QString* key() {return &usr_profile_struct.key_str;}
  QString* name() {return &usr_profile_struct.name_str;}
  QString* avatar() {return &usr_profile_struct.avatar_str;}
  QString* ip() {return &usr_profile_struct.ip_str;}
  int currentHistoryBundleIndex(){return current_history_bundle_index;}


private:

  UsrProfileStruct usr_profile_struct;

  const int max_bundle_capacity = 100;
  const QString app_data_local_path = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
  const QString usr_path = app_data_local_path + "/usr/";
  QString history_path;
  QString usr_key;

  int current_history_bundle_index;
  int latest_history_bundle_index;
  QList<QJsonObject> unread_message_list;//unused
  QList<QJsonObject> unread_message_buffer_list;
  QList<QJsonArray> history_bundle_list;//Boxes of canned patato chips
  QJsonArray latest_history_json_array;//Pieces of patato chips

  //Funciton
  bool checkDir(const QString &directory);
  void refreshUsrProfile(const UsrProfileStruct &usrProfileStruct);

  void readHistoryBundle();
  void makeHistoryBundle(int num);
  void saveHistoryBundle();
  void recordMessage(const MessageStruct &messageStruct, bool fromMe);
  void recordMessage(const QJsonObject &messageJsonObject);
  void recordMessage(const QList<QJsonObject> &messageJsonObjectList);

};

#endif // DATAUSER_H
