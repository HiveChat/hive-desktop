#ifndef HIVE_H
#define HIVE_H

#include "Log.h"
#include "DataManager.h"

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
  QThread *data_thread;
  QThread *net_thread;

  DataManager *data_manager;

signals:

public slots:
};

#endif // HIVE_H
