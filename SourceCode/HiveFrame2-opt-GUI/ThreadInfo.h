#ifndef THREADINFO_H
#define THREADINFO_H

#include "GlobalData.h"
#include "NetManager.h"

#include <QThread>
#include <QDebug>
#include <QCoreApplication>

class ThreadInfo : public QThread
{
  Q_OBJECT

public:
  explicit ThreadInfo(QObject *parent = 0);
  ~ThreadInfo();

protected:
  void run();

private:
  bool running = true;

  void checkNetConnection();

signals:
  void settingsChanged();

};

#endif // THREADINFO_H
