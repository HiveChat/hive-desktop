#ifndef HIVEPROTOCOL_H
#define HIVEPROTOCOL_H

#include "Log.h"
#include "UsrData.h"
#include "GlobalData.h"

class HiveProtocol
{



public:
  enum BaseProtocol{
    Any = 0,
    Udp = 1,
    Tcp = 2
  };

  struct HiveClientBuffer{
    QString buffer;
    int readSize = 0;
  };

  static bool decodeTcp(const QString &data, HiveClientBuffer *clientBuffer);
  static bool decodeUdp(const QString &data, const char *addr);
  static bool writeTcp(const MessageType &msgType, const QString &data);



protected:

  static inline bool decodeHivePacket(const QString &data, const QString &addr = "");

  static inline bool processHeartBeat(const UsrProfileStruct &usrProfileStruct);
  static inline bool processUsrLeave(QString *usrKey);
  static inline bool processErrorDelivery();
  static inline bool processTextMessage();
  static inline bool processFileInfo();
  static inline bool processFileContent();
  static inline bool processFileAccept();
  static inline bool processFileReject();

  static QByteArray encodeHeartBeat();
  static QByteArray encodeTextMessage(const QJsonObject &msg);

signals:
  void usrEntered(const UsrProfileStruct &usr);


};

#endif // HIVEPROTOCOL_H
