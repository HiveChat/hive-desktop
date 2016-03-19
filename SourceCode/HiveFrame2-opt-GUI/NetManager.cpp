#include "NetManager.h"
#include <QLabel>

NetManager::NetManager(QObject *parent) : QObject(parent)
{
  this->setParent(parent);

  udp_socket = new QUdpSocket(this);
  udp_socket->bind(udp_port, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);
  connect(udp_socket, SIGNAL(readyRead()), this, SLOT(processPendingDatagrams()));

  refreshLocalHostIP();

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

    out << Message << usrKeyStr << GlobalData::g_my_profile.key_str << message;
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

  out << UsrEnter << GlobalData::g_localHostIP << GlobalData::g_my_profile.key_str << GlobalData::g_my_profile.name_str << GlobalData::g_my_profile.avatar_str;
  qint64 f = udp_socket->writeDatagram(data, data.length(), QHostAddress::Broadcast, udp_port);

  qDebug()<<"finished$ void NetManager::sendUsrEnter()";
  return;
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

            if(object_key_str != GlobalData::g_my_profile.key_str)
              {
                if(subject_key_str != GlobalData::g_my_profile.key_str)
                  {
                    qDebug()<<"人家的事情我不管";
                    break;
                  }
                else
                  {
                    message_str_list.append(object_key_str);
                    message_str_list.append(subject_key_str);
                    message_str_list.append(message_str);
                    message_str_list.append(GlobalData::g_currentTime());

                    qDebug()<<"我发了消息："<<message_str_list[2];
                    emit messageRecieved(message_str_list, true);
                    break;
                  }
              }
            else
              {
                if(subject_key_str == GlobalData::g_my_profile.key_str)
                  {
                    qDebug()<<"我发给自己的消息";
                    break;
                  }
                else
                  {
                    message_str_list.append(object_key_str);
                    message_str_list.append(subject_key_str);
                    message_str_list.append(message_str);
                    message_str_list.append(GlobalData::g_currentTime());
                    qDebug()<<"别人发给我的："<<message_str_list.at(2);

                    emit messageRecieved(message_str_list, false);
                    break;
                  }
              }
            break;
          }//case

        case UsrEnter:
          {
            //out << UsrEnter << GlobalData::g_localHostIP << GlobalData::g_myKeyStr << GlobalData::my_info.usr_name << in_byte_array;
            UsrProfileStruct temp_usr_profile;

            in >> temp_usr_profile.ip_str;
            in >> temp_usr_profile.key_str;
            in >> temp_usr_profile.name_str;
            in >> temp_usr_profile.avatar_str;

            if(temp_usr_profile.key_str == GlobalData::g_my_profile.key_str)
              {
//                QStringList usr_info_str_list;
//                usr_info_str_list << temp_usr_profile.usr_key << temp_usr_profile.ip_addr << temp_usr_profile.usr_name << temp_usr_profile.avatar_path;
                emit usrEnter(&temp_usr_profile);

                qDebug()<<"UDP receive# Myself entered.";
                break;
              }

            qDebug()<<"UDP receive# Someone entered.";

//            QStringList usr_info_str_list;
//            usr_info_str_list << temp_usr_profile.usr_key << temp_usr_profile.ip_addr << temp_usr_profile.usr_name << temp_usr_profile.avatar_path;
            emit usrEnter(&temp_usr_profile);

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



void NetManager::refreshLocalHostIP()
{
  QList<QHostAddress> AddressList = QNetworkInterface::allAddresses();
  QHostAddress result;
  foreach(QHostAddress address, AddressList)
    {
      if(address.protocol() == QAbstractSocket::IPv4Protocol
         && address != QHostAddress::Null
         && address != QHostAddress::LocalHost)
        {
          if (!address.toString().contains("127.0."))
            {
              result = address;
              break;
            }
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
}

void NetManager::TEST()
{

  /////test

//  QList<QNetworkInterface> list = QNetworkInterface::allInterfaces();
//  foreach(QNetworkInterface interface,list)
//  {
//      qDebug() <<"Device:"<<interface.name();
//      qDebug() << "HardwareAddress:"<<interface.hardwareAddress();


//      QList<QNetworkAddressEntry> entryList = interface.addressEntries();
//   //获取IP地址条目列表，每个条目中包含一个IP地址，一个子网掩码和一个广播地址
//      foreach(QNetworkAddressEntry entry,entryList)
//      {
//          qDebug()<<"IP Address:"<<entry.ip().toString();
//          qDebug()<<"Netmask: "  <<entry.netmask().toString();
//          qDebug()<<"Broadcast:" <<entry.broadcast().toString();
//      }
//  }

  //qDebug()<<QNetworkInterface::allAddresses().at(0).toString()<<endl;
  /////!test

  //qDebug()<<QDateTime::currentDateTime().toString("yyyy_MM_dd_hh_mm_ss");

  TEST_sendMessage(GlobalData::g_my_profile.key_str,"0?-00-9E-9A-A4-FD", "Have dinner together?");
  TEST_sendMessage("0?-00-9E-9A-A4-FD",GlobalData::g_my_profile.key_str, "No way! ");
  TEST_sendMessage(GlobalData::g_my_profile.key_str,"87-00-9E-9A-A4-FD","Why write Hive?");
  TEST_sendMessage("87-00-9E-9A-A4-FD",GlobalData::g_my_profile.key_str,"Why do you ask?");
  TEST_sendMessage(GlobalData::g_my_profile.key_str,"87-00-9E-9A-A4-FD","Why can't I ask?");
  TEST_sendMessage("87-00-9E-9A-A4-FD",GlobalData::g_my_profile.key_str,"Yes you can, but you'd better ask James. I'm now debuging, sorry for that😂.\n\n");

//  for(int i = 0; i < 500; i++)
//  {
//      TEST_sendMessage(GlobalData::g_myKeyStr,"87-00-9E-9A-A4-FD","让自由之声从纽约州的崇山峻岭响起来！让自由之声从宾夕法尼亚州阿勒格尼山的顶峰响起！让自由之声从科罗拉多州冰雪覆盖的落矶山响起来！让自由之声从加利福尼亚州蜿蜒的群峰响起来！不仅如此，还要让自由之声从佐治亚州的石岭响起来！让自由之声从田纳西州的了望山响起来！让自由之声从密西西比州的每一座丘陵响起来！让自由之家，这个梦想必须实现。");
//  }
  TEST_sendMessage("45-00-9E-9A-A4-FD",GlobalData::g_my_profile.key_str,"fffffff3");
  TEST_sendMessage("44-00-9E-9A-A4-FD",GlobalData::g_my_profile.key_str,"fffffff4");
}
