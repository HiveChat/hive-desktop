#ifndef HIVEABSTRACTSERVER_H
#define HIVEABSTRACTSERVER_H

//#include <QJsonObject>
//#include <QJsonDocument>

#include <functional>
#include <Log.h>
#include <../libs/libParsley/src/PUdpSocket.h>

#include "GlobalData.h"

class HiveAbstractServer
{
public:
  typedef std::function<void (const QJsonObject &)> PacketReadyCb;

  virtual void bindCb(const PacketReadyCb &cb);

  void callPacketReady(const QJsonObject &packet);

protected:
  PacketReadyCb packet_ready_cb;

  bool checkJsonPackage(const QString &data, QJsonObject *obj);
};

#endif // HIVEABSTRACTSERVER_H
