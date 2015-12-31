#include "NetManager.h"

NetManager::NetManager(QObject *parent) : QObject(parent)
{

  udp_socket = new QUdpSocket(this);
  udp_socket->bind(udp_port, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);


}

NetManager::~NetManager()
{

}



void NetManager::sendMessage(QString ip_addr, QString message = "")
{
    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);

    if (message == "")
      {
        qDebug()<<"Message content empty!";
        return;
      }
    else
      {
        out << Message << ip_addr << message;
      }

    udp_socket->writeDatagram(data,data.length(),QHostAddress::Broadcast, udp_port);
}

