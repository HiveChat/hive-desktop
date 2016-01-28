#ifndef DATAHISTORYIO_H
#define DATAHISTORYIO_H

#include "DataManager.h"


class DataHistoryIO : public QObject
{
  Q_OBJECT

public:
  explicit DataHistoryIO(QString usrKey, QObject *parent = 0);
  ~DataHistoryIO();

  void readMessage(int index);

public slots:
  void wirteMessage(QStringList message, bool fromMe);


private:

  const QString app_data_local_path = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
  const QString usr_path = app_data_local_path + "/usr/";

  QString history_path;
  QString usr_key;

  int currentIndex;
  QList<QJsonObject> history_list;

  QList<QJsonObject> message_list;


  void makeHistoryFile(int num);
  void saveMessage(QList<QJsonObject> *messageList);


};

#endif // DATAHISTORYIO_H
