#include "TcpServer.h"

TcpServer::TcpServer()
{
  thread_pool = new QThreadPool(this);
  thread_pool->setMaxThreadCount(10);
  this->listen(QHostAddress::Any, 23233);

}

void TcpServer::incomingConnection(qintptr handle)
{
  if(tcp_socket_hash.contains(handle))
    {
      TcpRunnable *run = new TcpRunnable(tcp_socket_hash.value(handle));
      run->setAutoDelete(true);
      thread_pool->start(run);
    }
  else
    {      
      QTcpSocket *tcpSocket = new QTcpSocket();
      tcp_socket_hash.insert(handle, tcpSocket);
      connect(tcpSocket, &QTcpSocket::readyRead, this, &TcpServer::readData);
      connect(tcpSocket, &QTcpSocket::disconnected, [this]() {
          qDebug()<<"disconnected";
        });
      connect(tcpSocket, &QTcpSocket::destroyed, [this]() {
                qDebug()<<"destroyed";
              });
      tcpSocket->setSocketDescriptor(handle);



      TcpRunnable *run = new TcpRunnable(tcpSocket);
      run->setAutoDelete(true);
      thread_pool->start(run);
    }
}

void TcpServer::readData()
{

}


