#include "NetManager.h"

NetManager::NetManager(QObject *parent) : QObject(parent)
{

  /////test

  /*QList<QNetworkInterface> list = QNetworkInterface::allInterfaces();
      foreach(QNetworkInterface interface,list)
      {
          qDebug() <<"Device:"<<interface.name();
          qDebug() << "HardwareAddress:"<<interface.hardwareAddress();


          QList<QNetworkAddressEntry> entryList = interface.addressEntries();
       //获取IP地址条目列表，每个条目中包含一个IP地址，一个子网掩码和一个广播地址
          foreach(QNetworkAddressEntry entry,entryList)
          {
              qDebug()<<"IP Address:"<<entry.ip().toString();
              qDebug()<<"Netmask: "  <<entry.netmask().toString();
              qDebug()<<"Broadcast:" <<entry.broadcast().toString();
          }
  }*/

  //qDebug()<<QNetworkInterface::allAddresses().at(0).toString()<<endl;
  qDebug()<<QDateTime::currentDateTime().toString("yyyy_MM_dd_hh_mm_ss");
  udp_socket = new QUdpSocket(this);
  udp_socket->bind(udp_port, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);
  connect(udp_socket, SIGNAL(readyRead()), this, SLOT(processPendingDatagrams()));

  /////!test


  sendUsrEnter();

  sendMessage(GlobalData::g_myKeyStr,"fffffff1");
  sendMessage(GlobalData::g_myKeyStr,"fffffff2");
  sendMessage(GlobalData::g_myKeyStr,"fffffff3");
  sendMessage(GlobalData::g_myKeyStr,"fffffff4");

  this->setParent(parent);
}

NetManager::~NetManager()
{

}



void NetManager::sendMessage(QString usr_key_str, QString message = "")
{
    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);

    if (message == "")
      {
        qDebug()<<"Message content empty!";
        return;
      }

    out << Message << usr_key_str << message;
    udp_socket->writeDatagram(data,data.length(),QHostAddress::Broadcast, udp_port);
}

void NetManager::sendUsrEnter()
{
  QByteArray data;
  QDataStream out(&data, QIODevice::WriteOnly);

  out << UsrEnter << GlobalData::g_localHostIP << GlobalData::g_myKeyStr << GlobalData::g_myNameStr;
}

void NetManager::localHostIP()
{
  QString localHostName = QHostInfo::localHostName();
  QHostInfo info = QHostInfo::fromName(localHostName);
  GlobalData::g_localHostIP = info.addresses().first().toString();
}

void NetManager::processPendingDatagrams()
{
  while(udp_socket->hasPendingDatagrams())
    {
      QByteArray datagram;
      datagram.resize(udp_socket->pendingDatagramSize());
      udp_socket->readDatagram(datagram.data(), datagram.size());
      QDataStream in(&datagram, QIODevice::ReadOnly);

      int msgType;
      in >> msgType;

      QString usrName,ipAddr,msg;
      QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");

      switch(msgType)
      {
        case Message:
          {
            QStringList message_str_list;
            QString message_000;
            QString usrKey_000;

            in >> usrKey_000 >> message_000;

            message_str_list.append(usrKey_000);
            message_str_list.append(message_000);

            qDebug()<<"message sent by:"<<usrKey_000<<" content:"<<message_000;
            emit messageRecieved(message_str_list);
            break;
          }

        ////////////problem2016-01-06

//        case UsrEnter:
//          {

//            in >>usrName >>ipAddr;
//            usrEnter(usrName,ipAddr);
//            break;
//          }

//        case UsrLeft:
//            in >>usrName;
//            usrLeft(usrName,time);
//            break;

//        case FileName:
//          {
//            in >> usrName >> ipAddr;
//            QString clntAddr, fileName;
//            in >> clntAddr >> fileName;
//            hasPendingFile(usrName, ipAddr, clntAddr, fileName);
//            break;
//          }

//        case Refuse:
//          {
//            /*in >> usrName;
//            QString srvAddr;
//            in >> srvAddr;
//            QString ipAddr = getIP();

//            if(ipAddr == srvAddr)
//            {
//                srv->refused();
//            }
//            break;*/
//          }
      }
    }
}

