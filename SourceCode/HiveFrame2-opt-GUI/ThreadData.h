#ifndef THREADDATA_H
#define THREADDATA_H

#include <QThread>

class ThreadData : public QThread
{
  Q_OBJECT
public:
  explicit ThreadData(QObject *parent = 0);
  ~ThreadData();

protected:
  void run();

private:
  bool status;
  void setStatus(bool running);

};

#endif // THREADDATA_H
