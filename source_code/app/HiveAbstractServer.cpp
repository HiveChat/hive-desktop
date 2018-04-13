#include "HiveAbstractServer.h"


bool HiveAbstractServer::start()
{

}

bool HiveAbstractServer::stop()
{

}

void HiveAbstractServer::bindCb(const Parsley::AbstractSocket::SockReadyReadCb &cb)
{
  packet_ready_cb = cb;
}

void HiveAbstractServer::callPacketReady(Parsley::Buffer data, char *ip)
{
  if(packet_ready_cb)
    {
      packet_ready_cb(data, ip);
    }
}


