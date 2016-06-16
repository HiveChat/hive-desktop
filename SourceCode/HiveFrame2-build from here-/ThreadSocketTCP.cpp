#include "ThreadSocketTCP.h"

ThreadSocketTCP::ThreadSocketTCP(QObject *parent) : QThread(parent)
{

  tcp_port = 8723;
  initServer();
}

void ThreadSocketTCP::initServer()
{

}

void ThreadSocketTCP::sendData()
{

}

void ThreadSocketTCP::closeConnection()
{

}
