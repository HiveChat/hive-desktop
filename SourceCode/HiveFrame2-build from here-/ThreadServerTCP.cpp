#include "ThreadServerTCP.h"

ThreadServerTCP::ThreadServerTCP(QObject *parent) : QThread(parent)
{

  tcp_port = 8723;
  tcp_server = new QTcpServer(this);
  connect(tcp_server, SIGNAL(newConnection()), this, SLOT(sendData()));

  initServer();
}

void ThreadServerTCP::initServer()
{

}

void ThreadServerTCP::sendData()
{

}

void ThreadServerTCP::closeConnection()
{

}
