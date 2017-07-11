#ifndef HIVE_H
#define HIVE_H

#include "log.h"
#include "data_manager.h"
#include "_showcase.h"

#include <QApplication>
#include <QThread>

#ifdef Q_OS_OSX
#include <QFileOpenEvent>
#include <QtMac>
#endif

class Hive : public QApplication
{
  Q_OBJECT
public:
  explicit Hive(int &argc, char **argv);
  ~Hive();

  _Showcase *central_widget;

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
