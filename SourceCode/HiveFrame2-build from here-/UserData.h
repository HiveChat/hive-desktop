#ifndef DATAUSER_H
#define DATAUSER_H

#include <QObject>
#include "GlobalData.h"
#include "DataHistoryIO.h"

class UserData : public QObject
{
  Q_OBJECT
public:
  explicit UserData(const UsrProfileStruct *usr_profile_struct, QObject *parent = 0);

private:
  UsrProfileStruct *usr_profile_struct;
  DataHistoryIO *data_history_io;

  const QString app_data_local_path = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
  const QString usr_path = app_data_local_path + "/usr/";

  QString history_path;
  QString usr_key;

  int current_active_index;
  QList<QJsonObject> full_history_list;
  QJsonObject active_history_json_obj;
  QJsonArray active_history_json_array;

  int save_cout_down = 0;
};

#endif // DATAUSER_H
