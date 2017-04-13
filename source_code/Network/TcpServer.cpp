#include "TcpServer.h"


TcpRunnable::TcpRunnable(QTcpSocket *tcpSocket, const Task &task, const QByteArray &data)
  : tcp_socket(tcpSocket)
  , tcp_task(task)
  , buffer(data)
{
}

void TcpRunnable::run()
{
  switch (tcp_task) {
    case Read:
      {

        break;
      }
    case Write:
      {
        if(tcp_socket->state() == QTcpSocket::ConnectedState)
          {
            tcp_socket->write(buffer);
            tcp_socket->flush();
            tcp_socket->waitForBytesWritten(100);
            qDebug().noquote()<<"Socket:"<<tcp_socket->socketDescriptor()<< "done!";
          }

        break;
      }
    default:
      {

        break;
      }
    }


}



TcpServer::TcpServer()
{
  thread_pool = new QThreadPool(this);
  thread_pool->setMaxThreadCount(10);
  this->listen(QHostAddress::Any, 23233);

//  connectToPeer(".");

}

bool TcpServer::connectToPeer(const QString &usrKey)
{
  QTcpSocket *tcpSocket = new QTcpSocket();
  tcpSocket->connectToHost(QHostAddress("192.168.21.100"), 23233);
  connect(tcpSocket, SIGNAL(connected()), tcpSocket, SLOT(write("helloTim")));
}

void TcpServer::incomingConnection(qintptr handle)
{
  qDebug()<<handle;

//  if(tcp_socket_hash.contains(handle))
//    {
//      TcpRunnable *run = new TcpRunnable(tcp_socket_hash.value(handle));
//      run->setAutoDelete(true);
//      thread_pool->start(run);
//    }
//  else
//    {
//      QTcpSocket *tcpSocket = new QTcpSocket();
//      tcp_socket_hash.insert(handle, tcpSocket);
//      connect(tcpSocket, &QTcpSocket::readyRead, this, &TcpServer::readData);
//      connect(tcpSocket, &QTcpSocket::disconnected, [this]() {
//          qDebug()<<"disconnected";
//        });
//      connect(tcpSocket, &QTcpSocket::destroyed, [this]() {
//                qDebug()<<"destroyed";
//              });
//      tcpSocket->setSocketDescriptor(handle);

//      TcpRunnable *run = new TcpRunnable(tcpSocket);
//      run->setAutoDelete(true);
//      thread_pool->start(run);
//    }
}

void TcpServer::readData()
{
  qDebug()<<tcp_socket_hash.values().first()->readAll();
}


