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
  typedef std::function<void (char*, char*)> PacketReadyCb;

  virtual bool start();
  virtual bool stop();
  virtual void bindCb(const PacketReadyCb &cb);

  void callPacketReady(char *data, char *ip);

protected:
  //! TODO: Add uv_loop_t* handle to protected member for future memory recycle.
  PacketReadyCb packet_ready_cb;

  bool checkJsonPackage(const QString &data, QJsonObject *obj);
};

#endif // HIVEABSTRACTSERVER_H
