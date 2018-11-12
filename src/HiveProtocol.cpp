#include "HiveProtocol.h"

bool
HiveProtocol::decodeTcp(const QString &data, HiveClientBuffer *clientBuffer) //recursion decode
{
  qDebug()<<"\n\n";
  Log::net(Log::Info, "Bee::read()", "New READ section begins");
  if(data.isEmpty() && clientBuffer->buffer.isEmpty())
    {
      Log::net(Log::Warning, "Bee:read()", "data empty");
      return false;
    }

  Log::net(Log::Info, "Bee::read()", "Stream: " + data);
  Log::net(Log::Info, "Bee::read()", "Current Buffer Size: " + QString::number( clientBuffer->buffer.size()));

  clientBuffer->buffer.append(data);

  //if size header is 0
  if(clientBuffer->readSize == 0)
    {
      //if 16 digit size header is not complete, return
      if(clientBuffer->buffer.size() < 16)
        {
          Log::net(Log::Info, "Bee::read()", "Failed: value \"size\" in header is not complete");
          return false;
        }
      else
        {
          clientBuffer->readSize = clientBuffer->buffer.mid(0, 16).toInt();
          clientBuffer->buffer.remove(0, 16);
          Log::net(Log::Info, "Bee::read()", "Member clientBuffer->readSize is set to " + QString::number(clientBuffer->readSize));
        }
    }

  //if data is not complete, return
  if(clientBuffer->buffer.size() < clientBuffer->readSize)
    {
      Log::net(Log::Info, "Bee::read()", "Failed: buffer not filled.");
      return false;
    }
  else //else read
    {
      QString packet = clientBuffer->buffer.mid(0, clientBuffer->readSize - 1);
      clientBuffer->buffer.remove(0, clientBuffer->readSize - 1);
      clientBuffer->readSize = 0;

      Log::net(Log::Info, "Bee::read()", "Get packet: " + packet);

//      if(!decodeHivePacket(packet))
        {
          Log::net(Log::Warning, "bool Bee::readBuffer()", "Packet decode failed!");
          clientBuffer->buffer.clear();

          //have to reset the connection!

          return false;
        }
    }

  return decodeTcp("", clientBuffer);
}

bool HiveProtocol::decodeUdp(const QString &data, const char *addr)
{
  checkJson(data, QString::fromUtf8(addr));
}

bool
HiveProtocol::writeTcp(const MessageType &msgType, const QString &data)
{

}

std::tuple<MessageType, QJsonObject>
HiveProtocol::checkJson(const QString &data, const QString &addr)
{

  return {};
}

QByteArray HiveProtocol::encodeHeartBeat()
{
  QJsonObject jsonObj;
  jsonObj.insert("sender", Global::settings.profile_uuid_str);
  jsonObj.insert("receiver", "{00000000-0000-0000-0000-000000000000}");
  jsonObj.insert("name", Global::settings.profile_name_str);
  jsonObj.insert("avatar", Global::settings.profile_avatar_str);
  jsonObj.insert("msgType", MessageType::HeartBeat);
  jsonObj.insert("trash", "aiCheila7Ohm8thohquoPhoh9aequ8raa1");
  QJsonDocument jsonDoc(jsonObj);

  return jsonDoc.toJson() + "\0";
}

QByteArray HiveProtocol::encodeTextMessage(const QJsonObject &msg)
{
  QJsonObject jsonObj = msg;
  jsonObj.insert("index", QJsonValue(Global::getRandomString(8)));
  jsonObj.insert("msgType", MessageType::TextMessage);
  QJsonDocument jsonDoc(jsonObj);

  return jsonDoc.toJson() + "\0";
}
