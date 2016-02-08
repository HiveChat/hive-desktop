#include "NetManager.h"

NetManager::NetManager(QObject *parent) : QObject(parent)
{
  this->setParent(parent);

  udp_socket = new QUdpSocket(this);
  udp_socket->bind(udp_port, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);
  connect(udp_socket, SIGNAL(readyRead()), this, SLOT(processPendingDatagrams()));

  localHostIP();



  sendUsrEnter();
  TEST();
}

NetManager::~NetManager()
{

}


void NetManager::sendMessage(QString usrKeyStr, QString message = "")
{
    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);

    if(message == "")
      {
        qDebug()<<"Message content empty!";
        return;
      }

    out << Message << usrKeyStr << GlobalData::g_myKeyStr << message;
    udp_socket->writeDatagram(data,data.length(),QHostAddress::Broadcast, udp_port);
}

void NetManager::TEST_sendMessage(QString to, QString from, QString message)
{
  QByteArray data;
  QDataStream out(&data, QIODevice::WriteOnly);

  if (message == "")
    {
      qDebug()<<"Message content empty!";
      return;
    }

  out << Message << to << from << message;
  udp_socket->writeDatagram(data,data.length(),QHostAddress::Broadcast, udp_port);
}

void NetManager::sendUsrEnter()
{
  QByteArray data;
  QDataStream out(&data, QIODevice::WriteOnly);

  QFile file(GlobalData::g_avatarPathStr);
  if(!file.open(QIODevice::ReadOnly))
    {
      return;
    }
  QByteArray in_byte_array = file.readAll();
  file.flush();
  file.close();

  out << UsrEnter << GlobalData::g_localHostIP << GlobalData::g_myKeyStr << GlobalData::g_myNameStr << in_byte_array;
  qint64 f = udp_socket->writeDatagram(data, data.length(), QHostAddress::Broadcast, udp_port);
  qDebug()<<f;
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

      switch(msgType)
      {
        case Message:
          {
            QStringList message_str_list;

            QString object_key_str;
            QString subject_key_str;
            QString message_str;

            in >> object_key_str >> subject_key_str >> message_str;

            if(object_key_str != GlobalData::g_myKeyStr)
              {
                if(subject_key_str != GlobalData::g_myKeyStr)
                  {
                    qDebug()<<"nope";
                    break;
                  }
                else
                  {
                    message_str_list.append(object_key_str);
                    message_str_list.append(subject_key_str);
                    message_str_list.append(message_str);
                    message_str_list.append(GlobalData::g_currentTime());
                    qDebug()<<message_str_list[2];
                    emit messageRecieved(message_str_list, true);
                  }
              }
            else
              {
                if(subject_key_str == GlobalData::g_myKeyStr)
                  {
                    qDebug()<<"what?";
                    break;
                  }
                else
                  {
                    message_str_list.append(object_key_str);
                    message_str_list.append(subject_key_str);
                    message_str_list.append(message_str);
                    message_str_list.append(GlobalData::g_currentTime());
                    qDebug()<<"notfromme))))))))))))))))"<<message_str_list[2];

                    emit messageRecieved(message_str_list, false);
                  }
              }
          }//case

        ////////////problem2016-01-06

        case UsrEnter:
          {
            qDebug()<<"££££££££££££££££££££££££££££££££££";
            //out << UsrEnter << GlobalData::g_localHostIP << GlobalData::g_myKeyStr << GlobalData::g_myNameStr << in_byte_array;
            QString subject_ip_str;
            QString subject_key_str;
            QString subject_name_str;
            in >> subject_ip_str >> subject_key_str >> subject_name_str;
            if(subject_key_str == GlobalData::g_myKeyStr)
              {
                //break;
              }
            QByteArray subject_byte_array;
            in >> subject_byte_array;
            //QPixmap subject_avatar_pixmap = QPixmap.loadFromData(subject_byte_array);
            break;
          }

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



QString NetManager::localHostIP()
{
  QList<QHostAddress> AddressList = QNetworkInterface::allAddresses();
  QHostAddress result;
  foreach(QHostAddress address, AddressList)
    {
      if(address.protocol() == QAbstractSocket::IPv4Protocol
         && address != QHostAddress::Null
         && address != QHostAddress::LocalHost)
        {
          if (address.toString().contains("127.0."))
            {
            continue;
            }
          result = address;
          break;
        }
    }

  if(!result.isNull())
    {
      GlobalData::g_localHostIP = result.toString();
    }
  else
    {
      GlobalData::g_localHostIP = "";
    }

  return GlobalData::g_localHostIP;
}

void NetManager::TEST()
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
  /////!test

  //qDebug()<<QDateTime::currentDateTime().toString("yyyy_MM_dd_hh_mm_ss");

//  TEST_sendMessage("90-00-4E-9A-A4-FD",GlobalData::g_myKeyStr,"But one hundred years later, the Negro still is not free. One hundred years later, the life of the Negro is still sadly crippled by the manacles of segregation and the chains of discrimination. One hundred years later, the Negro lives on a lonely island of poverty in the midst of a vast ocean of material prosperity. One hundred years later, the Negro is still languished in the corners of American society and finds himself an exile in his own land. So we’ve come here today to dramatize a shameful condition.");
  TEST_sendMessage(GlobalData::g_myKeyStr,"87-00-9E-9A-A4-FD","如果美国要成为一个伟大的国家，这个梦想必须实现。让自由之声从新罕布什尔州的巍峨峰巅响起来！让自由之声从纽约州的崇山峻岭响起来！让自由之声从宾夕法尼亚州阿勒格尼山的顶峰响起！让自由之声从科罗拉多州冰雪覆盖的落矶山响起来！让自由之声从加利福尼亚州蜿蜒的群峰响起来！不仅如此，还要让自由之声从佐治亚州的石岭响起来！让自由之声从田纳西州的了望山响起来！让自由之声从密西西比州的每一座丘陵响起来！让自由之声从每一片山坡响起来r。");
//  TEST_sendMessage("87-00-9E-9A-A4-FD",GlobalData::g_myKeyStr,"如果美国要成为一个伟大的国家，这个梦想必须实现。让自由之声从新罕布什尔州的巍峨峰巅响起来！让自由之声从纽约州的崇山峻岭响起来！让自由之声从宾夕法尼亚州阿勒格尼山的顶峰响起！让自由之声从科罗拉多州冰雪覆盖的落矶山响起来！让自由之声从加利福尼亚州蜿蜒的群峰响起来！不仅如此，还要让自由之声从佐治亚州的石岭响起来！让自由之声从田纳西州的了望山响起来！让自由之声从密西西比州的每一座丘陵响起来！让自由之声从每一片山坡响起来。");
  TEST_sendMessage(GlobalData::g_myKeyStr,"87-00-9E-9A-A4-FD","如果美国要成为一个伟大的国家，这个梦想必须实现。让自由之声从新罕布什尔州的巍峨峰巅响起来！让自由之声从纽约州的崇山峻岭响起来！让自由之声从宾夕法尼亚州阿勒格尼山的顶峰响起！让自由之声从科罗拉多州冰雪覆盖的落矶山响起来！让自由之声从加利福尼亚州蜿蜒的群峰响起来！不仅如此，还要让自由之声从佐治亚州的石岭响起来！让自由之声从田纳西州的了望山响起来！让自由之声从密西西比州的每一座丘陵响起来！让自由之家，这个梦想必须实现。让自由之声从新罕布什尔州的巍峨峰巅响起来！让自由之声从纽约州的崇山峻岭响起来！让自由之声从宾夕法尼亚州阿勒格尼山的顶峰响起！让自由之声从科罗拉多州冰雪覆盖的落矶山响起来！让自由之声从加利福尼亚州蜿蜒的群峰响起来！不仅如此，还要让自由之声从佐治亚州的石岭响起来！让自由之声从田纳西州的了望山响起来！让自由之声从密西西比州的每一座丘陵响起来！让自由之家，这个梦想必须实现。让自由之声从新罕布什尔州的巍峨峰巅响起来！让自由之声从纽约州的崇山峻岭响起来！让自由之声从宾夕法尼亚州阿勒格尼山的顶峰响起！让自由之声从科罗拉多州冰雪覆盖的落矶山响起来！让自由之声从加利福尼亚州蜿蜒的群峰响起来！不仅如此，还要让自由之声从佐治亚州的石岭响起来！让自由之声从田纳西州的了望山响起来！让自由之声从密西西比州的每一座丘陵响起来！让自由之声从每一片山坡响起来。");
  TEST_sendMessage(GlobalData::g_myKeyStr,"87-00-9E-9A-A4-FD","如果美国要成为一个伟大的国家，这个梦想必须实现。让自由之声从新罕布什尔州的巍峨峰巅响起来！让自由之声从纽约州的崇山峻岭响起来！让自由之声从之声从密西西比州的每一座丘陵响起来！让自由之声从每一片山坡响起来。");
//  TEST_sendMessage("45-00-9E-9A-A4-FD",GlobalData::g_myKeyStr,"fffffff3");
//  TEST_sendMessage("44-00-9E-9A-A4-FD",GlobalData::g_myKeyStr,"fffffff4");
}
