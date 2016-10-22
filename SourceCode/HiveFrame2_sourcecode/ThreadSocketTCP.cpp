#include "ThreadSocketTCP.h"

ThreadSocketTCP::ThreadSocketTCP(const qint16 &port, QObject *parent) : QThread(parent)
{
  tcp_port = port;
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
