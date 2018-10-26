#ifndef HIVEPROTOCOL_H
#define HIVEPROTOCOL_H

#include "Log.h"
#include "UsrData.h"
#include "Global.h"

class HiveProtocol
{
public:
  struct HiveClientBuffer{
    QString buffer;
    int readSize = 0;
  };

  static bool decodeTcp(const QString &data, HiveClientBuffer *clientBuffer);
  static bool decodeUdp(const QString &data, const char *addr);
  static bool writeTcp(const MessageType &msgType, const QString &data);

  static QByteArray encodeHeartBeat();

protected:
  static std::tuple<MessageType, QJsonObject> checkJson(const QString &data, const QString &addr = "");



  static QByteArray encodeTextMessage(const QJsonObject &msg);

signals:
  void usrEntered(const UsrProfile &usr);


};

#endif // HIVEPROTOCOL_H
