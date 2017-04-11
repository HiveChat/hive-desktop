#include "TcpRunnable.h"
#include <QDebug>

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
      break;
    }


}


