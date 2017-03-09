#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QJsonObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QThread>
#include <QHash>

class TcpServer : public QTcpServer
{
  Q_OBJECT
public:
  explicit TcpServer(QObject *parent = 0, const int &maxPendingConnections = 100);

protected:
  void incomingConnection(qintptr socketDescriptor);

private:
  QHash<int, QTcpSocket*> tcp_socket_map;


};

#endif // TCPSERVER_H
