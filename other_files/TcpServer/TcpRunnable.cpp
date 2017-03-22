#include "TcpRunnable.h"
#include <QDebug>

TcpRunnable::TcpRunnable(QTcpSocket *tcpSocket)
  : tcp_socket(tcpSocket)
{

}

void TcpRunnable::run()
{

  for(int i = 0; i < 10000000; i++)
    {
      if(tcp_socket->state() == QTcpSocket::ConnectedState)
        {
          tcp_socket->write("hello?");
          tcp_socket->flush();
//          tcp_socket->waitForBytesWritten(500);

          qDebug().noquote()<<"Socket:"<<tcp_socket->socketDescriptor()<< "count: " << i;
        }
    }

  qDebug().noquote()<<"Socket:"<<tcp_socket->socketDescriptor()<< "done!";
}


