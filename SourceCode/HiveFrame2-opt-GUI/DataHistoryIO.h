#ifndef DATAHISTORYIO_H
#define DATAHISTORYIO_H

#include "DataManager.h"


class DataHistoryIO : public QObject
{
  Q_OBJECT

public:
  explicit DataHistoryIO(QString usrKey, QObject *parent = 0);
  ~DataHistoryIO();

private:
  QString usr_key;
};

#endif // DATAHISTORYIO_H
