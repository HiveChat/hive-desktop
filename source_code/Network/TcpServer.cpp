#include "TcpServer.h"

TcpServer::TcpServer(QObject *parent, const int &maxPendingConnections) : QTcpServer(parent)
{
  this->setMaxPendingConnections(maxPendingConnections);
}

void TcpServer::incomingConnection(qintptr socketDescriptor)
{
//  QThread *thread = new QThread(this);
//  QTcpSocket *tcp_socket = new QTcpSocket();
}
