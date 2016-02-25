#ifndef THREADINFO_H
#define THREADINFO_H

#include <QThread>

class ThreadInfo : public QThread
{
  Q_OBJECT

public:
  explicit ThreadInfo(QThread *parent = 0);
  ~ThreadInfo();

protected:
  void run();
};

#endif // THREADINFO_H
