#ifndef TCPRUNNABLE_H
#define TCPRUNNABLE_H

#include <QObject>
#include <QRunnable>
#include <QTcpSocket>
#include <QThread>

class TcpRunnable : public QRunnable
{
  enum Task{
    Read,
    Write
  };

public:
  explicit TcpRunnable(QTcpSocket *tcpSocket, const Task &task, const QByteArray &data);

protected:
  void run();

private:
  Task tcp_task;
  QByteArray buffer;
  QTcpSocket *tcp_socket;

};

#endif // TCPRUNNABLE_H
