#ifndef DATAHISTORYIO_H
#define DATAHISTORYIO_H

#include "DataManager.h"

#include <QObject>




class DataHistoryIO : public QObject
{
  Q_OBJECT

public:
  explicit DataHistoryIO(QString usrKey, QObject *parent = 0);
  ~DataHistoryIO();

private:
  QString usr_key;

  bool checkDir(QString dir);
};

#endif // DATAHISTORYIO_H
