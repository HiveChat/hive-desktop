#ifndef UVTCPSERVER_H
#define UVTCPSERVER_H

#include <QThread>
#include <uv.h>
#include <QDebug>

class tcpOp
{
public:
  tcpOp(){}

  static int64_t counter;

  static void wait_for_a_while(uv_idle_t* handle) {
      sleep(1);
      qDebug()<<counter++;

      if (counter >= 10)
        {
          uv_idle_stop(handle);
        }
  }
};


class UvTcpServer : public QThread
{
  Q_OBJECT
public:
  explicit UvTcpServer(QObject *parent = 0);

protected:
  void run();

public slots:
};

#endif // UVTCPSERVER_H
