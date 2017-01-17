#include "TcpServer.h"

TcpServer::TcpServer(QObject *parent, const int &maxPendingConnections) : QTcpServer(parent)
{
  this->setMaxPendingConnections(maxPendingConnections);
}

void TcpServer::incomingConnection(qintptr socketDescriptor)
{
  if (tcp_socket_map.size() > maxPendingConnections())
  {
      QTcpSocket tcp;
      tcp.setSocketDescriptor(socketDescriptor);
      tcp.disconnectFromHost();
      return;
  }
//  QThread *thread = new QThread(this);
//  QTcpSocket *tcp_socket = new QTcpSocket();
}
