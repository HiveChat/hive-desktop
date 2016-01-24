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

  sendMessage("90-00-4E-9A-A4-FD","But one hundred years later, the Negro still is not free. One hundred years later, the life of the Negro is still sadly crippled by the manacles of segregation and the chains of discrimination. One hundred years later, the Negro lives on a lonely island of poverty in the midst of a vast ocean of material prosperity. One hundred years later, the Negro is still languished in the corners of American society and finds himself an exile in his own land. So we’ve come here today to dramatize a shameful condition.");
  sendMessage("87-00-9E-9A-A4-FD","如果美国要成为一个伟大的国家，这个梦想必须实现。让自由之声从新罕布什尔州的巍峨峰巅响起来！让自由之声从纽约州的崇山峻岭响起来！让自由之声从宾夕法尼亚州阿勒格尼山的顶峰响起！让自由之声从科罗拉多州冰雪覆盖的落矶山响起来！让自由之声从加利福尼亚州蜿蜒的群峰响起来！不仅如此，还要让自由之声从佐治亚州的石岭响起来！让自由之声从田纳西州的了望山响起来！让自由之声从密西西比州的每一座丘陵响起来！让自由之声从每一片山坡响起来。");
  sendMessage("87-00-9E-9A-A4-FD","如果美国要成为一个伟大的国家，这个梦想必须实现。让自由之声从新罕布什尔州的巍峨峰巅响起来！让自由之声从纽约州的崇山峻岭响起来！让自由之声从宾夕法尼亚州阿勒格尼山的顶峰响起！让自由之声从科罗拉多州冰雪覆盖的落矶山响起来！让自由之声从加利福尼亚州蜿蜒的群峰响起来！不仅如此，还要让自由之声从佐治亚州的石岭响起来！让自由之声从田纳西州的了望山响起来！让自由之声从密西西比州的每一座丘陵响起来！让自由之声从每一片山坡响起来。");
  sendMessage("87-00-9E-9A-A4-FD","如果美国要成为一个伟大的国家，这个梦想必须实现。让自由之声从新罕布什尔州的巍峨峰巅响起来！让自由之声从纽约州的崇山峻岭响起来！让自由之声从宾夕法尼亚州阿勒格尼山的顶峰响起！让自由之声从科罗拉多州冰雪覆盖的落矶山响起来！让自由之声从加利福尼亚州蜿蜒的群峰响起来！不仅如此，还要让自由之声从佐治亚州的石岭响起来！让自由之声从田纳西州的了望山响起来！让自由之声从密西西比州的每一座丘陵响起来！让自由之家，这个梦想必须实现。让自由之声从新罕布什尔州的巍峨峰巅响起来！让自由之声从纽约州的崇山峻岭响起来！让自由之声从宾夕法尼亚州阿勒格尼山的顶峰响起！让自由之声从科罗拉多州冰雪覆盖的落矶山响起来！让自由之声从加利福尼亚州蜿蜒的群峰响起来！不仅如此，还要让自由之声从佐治亚州的石岭响起来！让自由之声从田纳西州的了望山响起来！让自由之声从密西西比州的每一座丘陵响起来！让自由之家，这个梦想必须实现。让自由之声从新罕布什尔州的巍峨峰巅响起来！让自由之声从纽约州的崇山峻岭响起来！让自由之声从宾夕法尼亚州阿勒格尼山的顶峰响起！让自由之声从科罗拉多州冰雪覆盖的落矶山响起来！让自由之声从加利福尼亚州蜿蜒的群峰响起来！不仅如此，还要让自由之声从佐治亚州的石岭响起来！让自由之声从田纳西州的了望山响起来！让自由之声从密西西比州的每一座丘陵响起来！让自由之声从每一片山坡响起来。");
  sendMessage("87-00-9E-9A-A4-FD","如果美国要成为一个伟大的国家，这个梦想必须实现。让自由之声从新罕布什尔州的巍峨峰巅响起来！让自由之声从纽约州的崇山峻岭响起来！让自由之声从之声从密西西比州的每一座丘陵响起来！让自由之声从每一片山坡响起来。");
  sendMessage("45-00-9E-9A-A4-FD","fffffff3");
  sendMessage("44-00-9E-9A-A4-FD","fffffff4");

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

