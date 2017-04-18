#ifndef SERVER_H
#define SERVER_H

#include <QHash>
#include <QTcpServer>
#include <QRunnable>
#include <QThreadPool>
#include <QtConcurrent>
#include "TcpRunnable.h"


class TcpServer : public QTcpServer
{
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
