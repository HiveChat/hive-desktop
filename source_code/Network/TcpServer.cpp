#include "TcpServer.h"

TcpServer::TcpServer(QObject *parent, const int &maxPendingConnections) : QTcpServer(parent)
{
  this->setMaxPendingConnections(maxPendingConnections);
}

void TcpServer::incomingConnection(qintptr socketDescriptor)
{
  if (tcp_socket_map.size() > maxPendingConnections())//继承重写此函数后，QTcpServer默认的判断最大连接数失效，自己实现
  {
      QTcpSocket tcp;
      tcp.setSocketDescriptor(socketDescriptor);
      tcp.disconnectFromHost();
      qDebug()<<"@TcpServer::incomingConnection(): Denial of Services, tcp_socket_map.size() > maxPendingConnections()";
      return;
  }

  QThread *thread = new QThread(this);
  thread->start(QThread::NormalPriority);

  QTcpSocket *tcp_socket = new QTcpSocket();
  tcp_socket->setSocketDescriptor(socketDescriptor);
  tcp_socket->moveToThread(thread);


}
