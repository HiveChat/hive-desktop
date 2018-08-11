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
  virtual bool start();
  virtual bool stop();
  virtual void bindCb(const Parsley::AbstractSocket::SockReadyReadCb &cb);

  template <class T, typename Ret, typename... Args>
  void bindCbb(Parsley::AbstractSocket::CallbackType &t, T *obj, Ret(T::*f)(Args...)) {
//    switch (t)
//      {
//      case Parsley::AbstractSocket::ReadyRead:
//        packet_ready_cb =
//        break;
//      default:
//        break;
//      }
  }

  void callPacketReady(Parsley::Buffer data, char *ip);

protected:
  Parsley::AbstractSocket::SockReadyReadCb packet_ready_cb;
};

#endif // HIVEABSTRACTSERVER_H
