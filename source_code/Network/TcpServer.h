#ifndef SERVER_H
#define SERVER_H

#include <QHash>
#include <QTcpServer>
#include <QTcpSocket>
#include <QRunnable>
#include <QThreadPool>

class TcpServer;
class TcpRunnable;

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



class TcpServer : public QTcpServer
{
  Q_OBJECT

public:
  explicit TcpServer();
  bool connectToPeer(const QString &usrKey);

protected:
  void incomingConnection(qintptr handle);

private:
  QHash<QString, QTcpSocket *> tcp_socket_hash;
  QHash<QString, qintptr> socket_discriptor_hash;
  QThreadPool *thread_pool;

private slots:
  void readData();

};

#endif // SERVER_H
