#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QJsonObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QThreadPool>
#include <QHash>

class TcpServer : public QTcpServer
{
  Q_OBJECT
public:
  explicit TcpServer(QObject *parent = 0, const int &maxPendingConnections = 100);
  bool startServer();

protected:
  void incomingConnection(qintptr socketDescriptor);

private:
  qint16 tcp_port = 23232;
  QHash<QString, QTcpSocket*> tcp_socket_map;



};



class TcpSocket : public QTcpSocket
{
  Q_OBJECT
public:
  explicit TcpSocket(const qintptr &socketDescriptor, QObject *parent = 0);

protected:

private:
  qintptr socket_descriptor;
  QHash<QString, QTcpSocket*> tcp_socket_map;



};



#endif // TCPSERVER_H
