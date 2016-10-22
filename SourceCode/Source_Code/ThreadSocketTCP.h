#ifndef THREADFILETCP_H
#define THREADFILETCP_H

#include <QThread>
#include <QTcpSocket>
#include <QFile>

class ThreadSocketTCP : public QThread
{
  Q_OBJECT
public:
  explicit ThreadSocketTCP(const qint16 &port, QObject *parent = 0);

private:
  qint16 tcp_port;
  QString file_name;
  QFile *local_file;

  QTcpSocket *tcp_socket;

  void initServer();
  void sendData();
  void closeConnection();
};

#endif // THREADFILETCP_H
