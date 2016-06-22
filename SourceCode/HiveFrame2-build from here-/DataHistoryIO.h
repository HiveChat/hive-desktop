#ifndef DATAHISTORYIO_H
#define DATAHISTORYIO_H

#include "ThreadData.h"

class DataHistoryIO : public QObject
{
  Q_OBJECT

public:
  explicit DataHistoryIO(const QString &usrKey, QObject *parent = 0);
  ~DataHistoryIO();

  QJsonArray readMessage(int index);
  int currentActiveIndex();

public slots:
  void wirteMessage(MessageStruct messageStruct, bool fromMe);


private:

  const QString app_data_local_path = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
  const QString usr_path = app_data_local_path + "/usr/";

  QString history_path;
  QString usr_key;

  int current_active_index;
  QList<QJsonObject> history_bundle_list;
  QJsonObject active_history_json_obj;
  QJsonArray active_history_json_array;

  int save_cout_down = 0;

  void makeHistoryFile(int num);
  void saveMessage();

};

#endif // DATAHISTORYIO_H
