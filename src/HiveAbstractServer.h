#ifndef HIVEABSTRACTSERVER_H
#define HIVEABSTRACTSERVER_H

//#include <QJsonObject>
//#include <QJsonDocument>

#include "Global.h"
#include "../libs/libParsley/include/PUdpSocket.h"

#include <functional>
#include <Log.h>


class HiveAbstractServer
{
public:
  virtual bool start();
  virtual bool stop();

  void callPacketReady(Parsley::Buffer data, char *ip);

protected:
//  Parsley::Callback packet_ready_cb;
};

#endif // HIVEABSTRACTSERVER_H
