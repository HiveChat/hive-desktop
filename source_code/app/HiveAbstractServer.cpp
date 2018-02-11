#include "HiveAbstractServer.h"


bool HiveAbstractServer::start()
{

}

bool HiveAbstractServer::stop()
{

}

void HiveAbstractServer::bindCb(const PacketReadyCb &cb)
{
  packet_ready_cb = cb;
}

void HiveAbstractServer::callPacketReady(const QJsonObject &packet)
{
  if(packet_ready_cb)
    {
      packet_ready_cb(packet);
    }
}

bool HiveAbstractServer::checkJsonPackage(const QString &data, QJsonObject *obj)
{
  QJsonParseError jsonError;
  QJsonDocument jsonDocument = QJsonDocument::fromJson(data.toLatin1(), &jsonError);
  if(jsonError.error != QJsonParseError::NoError
     || !jsonDocument.isObject())
    {
      Log::net(Log::Critical
               , "HiveAbstractServer::checkJsonPackage()"
               , QString(jsonError.errorString() + " in stream: " + data));
      return false;
    }

  QJsonObject json = jsonDocument.object();
  QString receiverKey = json.value("receiver").toString();
  if(receiverKey != Global::settings.profile_key_str
     && receiverKey != "{00000000-0000-0000-0000-000000000000}")
    {
      Log::net(Log::Error
               , "HiveAbstractServer::checkJsonPackage()"
               , "Package belongs to " + json.value("receiver").toString());
      return false;
    }
  else
    {
      *obj = json;
      return true;
    }
}
