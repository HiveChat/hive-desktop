#ifndef DATAUSER_H
#define DATAUSER_H

#include <QObject>
#include <QtConcurrent>
#include "ThreadData.h"

class UserData : public QObject
{
  Q_OBJECT
public:
  explicit UserData(const UsrProfileStruct &usr_profile_struct, QObject *parent = 0);
  ~UserData();
private:
  void refreshUsrProfile(const UsrProfileStruct &usrProfileStruct);

  void readHistoryBundle();
  void makeHistoryBundle(int num);
  void saveHistoryBundle();
  void recordMessage(MessageStruct messageStruct, bool fromMe);

  UsrProfileStruct usr_profile_struct;

  const int max_bundle_capacity = 100;
  const QString app_data_local_path = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
  const QString usr_path = app_data_local_path + "/usr/";

  QString history_path;
  QString usr_key;

  int current_history_bundle_index;
  QList<QJsonObject> history_bundle_list;
  QJsonArray current_history_json_array;

};

#endif // DATAUSER_H
