#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include "AppData.h"

#include <QDebug>
#include <QObject>

class DataManager : public QObject
{
  Q_OBJECT
public:
  explicit DataManager(QObject *parent = 0);

  void init();


private:
  inline void loadAppDataTable();

signals:

public slots:
};

#endif // DATAMANAGER_H
