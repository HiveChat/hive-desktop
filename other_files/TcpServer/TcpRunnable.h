#ifndef TCPRUNNABLE_H
#define TCPRUNNABLE_H

#include <QObject>
#include <QRunnable>
#include <QTcpSocket>
#include <QThread>

class TcpRunnable : public QRunnable
{
public:
  explicit TcpRunnable(QTcpSocket *tcpSocket);

protected:
  void run();

private:
  QTcpSocket *tcp_socket;

};

#endif // TCPRUNNABLE_H
