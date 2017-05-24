#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include "global_var.h"

#include <QDebug>
#include <QObject>

class AppDataManager : public QObject
{
  Q_OBJECT
public:
  explicit AppDataManager(QObject *parent = 0);

  void init();


private:
  inline void loadAppDataTable();

signals:

public slots:
};

#endif // DATAMANAGER_H
