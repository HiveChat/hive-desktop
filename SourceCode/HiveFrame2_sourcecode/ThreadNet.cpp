#include "ThreadNet.h"

ThreadNet::ThreadNet(QObject *parent) : QThread(parent)
{

  tcp_server = new QTcpServer(this);
  connect(tcp_server, SIGNAL(newConnection()), this, SLOT(tcpSendData()));
  tcpInitServer();

  udp_socket = new QUdpSocket(this);
  udp_socket->bind(udp_port, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);
  connect(udp_socket, SIGNAL(readyRead()), this, SLOT(udpProcessPendingDatagrams()));
  udpSendUsrEnter();//this can be deleted
}

ThreadNet::~ThreadNet()
{
//  udpSendUsrLeave();

  QMutex mutex;
  mutex.lock();
  running = false;
  mutex.unlock();

  qDebug()<<"ThreadNet destructed";
}

////////run
void ThreadNet::run()
{
  QMutex mutex;
  while(this->isRunning())
    {
      mutex.lock();

      if(loop_count%1 == 0)
        {
          refreshLocalHostIP();
        }

      if(loop_count%2 == 0)
        {

        }

      if(loop_count%5 == 0)
        {
          sendOnlineStatus();
        }

      if(loop_count%10 == 0)
        {

          loop_count = 0;
        }

      loop_count ++;
      mutex.unlock();
      msleep(1000);
    }
}


void ThreadNet::refreshLocalHostIP()
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
  qDebug()<<"@refreshLocalHostIP(): finished!";
}

void ThreadNet::sendOnlineStatus()
{
  if(!GlobalData::g_localHostIP.isEmpty())
    {
      udpSendUsrEnter();
    }
}

///udp process
void ThreadNet::udpProcessMessage(MessageStruct *messageStruct)
{
  if(messageStruct->sender_key.isEmpty() || messageStruct->reciever_key.isEmpty())
    {
      return;
    }

  if(messageStruct->reciever_key != GlobalData::g_settings_struct.profile_key_str)
    {
      if(messageStruct->sender_key != GlobalData::g_settings_struct.profile_key_str)
        {
          //no sniffing
          return;
        }
      else
        {
          qDebug()<<"@ThreadNet::udpProcessMessage(): Got msg I sent: "<<messageStruct->message_str;
          messageStruct->time_str =  GlobalData::g_currentTime();
          emit messageRecieved(messageStruct, true);
        }
    }
  else
    {
      if(messageStruct->sender_key == GlobalData::g_settings_struct.profile_key_str)
        {
          qDebug()<<"@ThreadNet::udpProcessMessage(): me 2 me...";
          messageStruct->time_str =  GlobalData::g_currentTime();
          emit messageRecieved(messageStruct, true);
        }
      else
        {
          qDebug()<<"@ThreadNet::udpProcessMessage(): Other people sent: "<<messageStruct->message_str;
          messageStruct->time_str =  GlobalData::g_currentTime();
          emit messageRecieved(messageStruct, false);
        }
    }
}

void ThreadNet::udpProcessUsrEnter(UsrProfileStruct *usrProfileStruct)
{
  if(usrProfileStruct->key_str.isEmpty())
    {
      return;
    }

  if(usrProfileStruct->key_str == GlobalData::g_settings_struct.profile_key_str)
    {
      qDebug()<<"@ThreadNet::udpProcessUsrEnter(): Myself entered.";
      emit usrEnter(usrProfileStruct);
    }
  else
    {
      qDebug()<<"@ThreadNet::udpProcessUsrEnter(): Someone entered.";
      emit usrEnter(usrProfileStruct);
    }

}

void ThreadNet::udpProcessUsrLeft(QString *usrKey)
{
  if(usrKey == GlobalData::g_settings_struct.profile_key_str)
    {
      emit usrLeft(usrKey);

      qDebug()<<"@ThreadNet::udpProcessUsrLeft(): Myself left.";
    }

  qDebug()<<"@ThreadNet::udpProcessUsrLeft(): Someone left.";
  emit usrLeft(usrKey);
}

void ThreadNet::udpProcessFileTran(const FileInfoStruct &fileInfoStruct)
{

}

///UDP Action
void ThreadNet::udpSendUsrEnter()
{
  QByteArray data;
  QDataStream out(&data, QIODevice::WriteOnly);

  out << UsrEnter;
  out << GlobalData::g_localHostIP;
  out << GlobalData::g_settings_struct.profile_key_str;
  out << GlobalData::g_settings_struct.profile_name_str;
  out << GlobalData::g_settings_struct.profile_avatar_str;

  /*qint64 f = */udp_socket->writeDatagram(data, data.length(), QHostAddress::Broadcast, udp_port);

  qDebug()<<"@sendUsrEnter(): finished!";
  return;
}

void ThreadNet::udpSendUsrLeave()
{
  QByteArray data;
  QDataStream out(&data, QIODevice::WriteOnly);
  out << UsrLeave << GlobalData::g_settings_struct.profile_key_str;
  udp_socket->writeDatagram(data,data.length(),QHostAddress::Broadcast, udp_port);

  qDebug()<<"@sendUsrLeave(): Finished!";
}

void ThreadNet::udpSendMessage(QString usrKeyStr, QString message)
{
  QByteArray data;
  QDataStream out(&data, QIODevice::WriteOnly);

  if(message.isEmpty())
    {
      qDebug()<<"@sendMessage(): Message content empty!";
      return;
    }

  qDebug()<<"@sendMessage(): Message Sent!";

  out << Message << usrKeyStr << GlobalData::g_settings_struct.profile_key_str << message;
  udp_socket->writeDatagram(data,data.length(),QHostAddress::Broadcast, udp_port);
}

void ThreadNet::udpSendFileTran()
{

}

void ThreadNet::udpSendFileAccept()
{

}

void ThreadNet::TEST_udpsSendMessage(QString to, QString from, QString message)
{
  QByteArray data;
  QDataStream out(&data, QIODevice::WriteOnly);

  if (message.isEmpty())
    {
      qDebug()<<"@sendMessage(): Message content empty!";
      return;
    }

  out << Message << to << from << message;
  udp_socket->writeDatagram(data,data.length(),QHostAddress::Broadcast, udp_port);
}

void ThreadNet::udpProcessFileReject()
{

}





void ThreadNet::tcpInitServer()
{

}

void ThreadNet::tcpSendData()
{

}

void ThreadNet::tcpCloseConnection()
{

}


/////////////private slots////////////

void ThreadNet::udpProcessPendingDatagrams()
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
            MessageStruct message;
            in >> message.reciever_key;
            in >> message.sender_key;
            in >> message.message_str;

            udpProcessMessage(&message);
            break;
          }
        case UsrEnter:
          {
            UsrProfileStruct usr_profile;
            in >> usr_profile.ip_str;
            in >> usr_profile.key_str;
            in >> usr_profile.name_str;
            in >> usr_profile.avatar_str;

            udpProcessUsrEnter(&usr_profile);
            break;
          }
        case UsrLeave:
          {


          }
        case FileReject:
          {


          }
        case FileTran:
          {
            FileInfoStruct file_info_struct;
            in >> file_info_struct.name;
            in >> file_info_struct.size;
            in >> file_info_struct.type;

            udpProcessFileTran(file_info_struct);
            break;
          }
      }
    }
}

