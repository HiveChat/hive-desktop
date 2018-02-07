#include "Bee.h"

Bee::Bee(char *uuid)
  : uuid(uuid)
{

}

bool Bee::isOnline() const
{
  return online;
}

void Bee::setOnline(const bool &value)
{
  online = value;
}

QString Bee::getIpAddr() const
{
  return ip_addr;
}

QString Bee::getHomeDir()
{

}

void Bee::setIpAddr(const QString &addr)
{
  ip_addr = addr;
}

QString Bee::getUuid() const
{
  return uuid;
}
