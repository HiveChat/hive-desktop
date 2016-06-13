#ifndef THREADFILETCP_H
#define THREADFILETCP_H

#include <QThread>
#include <QTcpServer>
#include <QTcpSocket>
#include <QFile>

class ThreadServerTCP : public QThread
{
  Q_OBJECT
public:
  explicit ThreadServerTCP(QObject *parent = 0);

private:
  qint16 tcp_port;
  QString file_name;
  QFile *local_file;

  QTcpServer *tcp_server;
  QTcpSocket *tcp_socket;

  void initServer();
  void sendData();
  void closeConnection();
};

#endif // THREADFILETCP_H
