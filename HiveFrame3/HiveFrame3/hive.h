#ifndef HIVE_H
#define HIVE_H

#include "log.h"
#include "app_data_manager.h"

#include <QApplication>
#include <QThread>

#ifdef Q_OS_OSX
#include <QFileOpenEvent>
#include <QtMac>
#endif

class HiveApp : public QApplication
{
  Q_OBJECT
public:
  explicit HiveApp(int &argc, char **argv);

protected:
  bool event(QEvent* event);

private:
  QThread *thread_data;
  QThread *thread_net;

  AppDataManager *data_manager;

signals:

public slots:
};

#endif // HIVE_H
