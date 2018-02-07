#ifndef BEE_H
#define BEE_H

#include <QString>

class Bee
{
public:
  Bee(char *uuid);

  bool isOnline() const;
  QString getUuid() const;
  QString getIpAddr() const;
  QString getHomeDir();

  void setOnline(const bool &value = true);
  void setIpAddr(const QString &addr);



private:
  bool online;
  QString uuid;
  QString ip_addr;

};

#endif // BEE_H
