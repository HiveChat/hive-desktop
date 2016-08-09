#ifndef DATAUSER_H
#define DATAUSER_H

#include <QObject>
#include <QtConcurrent>
#include "GlobalType.h"
//#include "ThreadData.h"//delete?



class UserData;

class UserData : public QObject
{
  Q_OBJECT
public:
  explicit UserData(const UsrProfileStruct &usrProfileStruct, QObject *parent = 0);
  ~UserData();

  void setUsrProfileStruct(const UsrProfileStruct &usrProfileStruct);

  int currentHistoryBundleIndex(){return current_history_bundle_index;}
  QJsonArray* flipLatest();
  QJsonArray* flipUp();
  QJsonArray* flipDown();

  UsrProfileStruct* usrProfileStruct(){return &usr_profile_struct;}
  QString* key() {return &usr_profile_struct.key_str;}
  QString* name() {return &usr_profile_struct.name_str;}
  QString* avatar() {return &usr_profile_struct.avatar_str;}
  QString* ip() {return &usr_profile_struct.ip_str;}


private:

  UsrProfileStruct usr_profile_struct;

  const int max_bundle_capacity = 100;
  const QString app_data_local_path = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
  const QString usr_path = app_data_local_path + "/usr/";
  QString history_path;
  QString usr_key;

  int current_history_bundle_index;
  int latest_history_bundle_index;
  QList<QJsonArray> history_bundle_list;
  QJsonArray latest_history_json_array;

  //Funciton
  bool checkDir(const QString &directory);
  void refreshUsrProfile(const UsrProfileStruct &usrProfileStruct);

  void readHistoryBundle();
  void makeHistoryBundle(int num);
  void saveHistoryBundle();
  void recordMessage(MessageStruct messageStruct, bool fromMe);

};

#endif // DATAUSER_H
