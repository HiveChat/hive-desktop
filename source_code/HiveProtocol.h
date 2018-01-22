#ifndef HIVEPROTOCOL_H
#define HIVEPROTOCOL_H

#include "Log.h"
#include "UsrData.h"
#include "GlobalData.h"

class HiveProtocol/* : public QObject*/
{
//  Q_OBJECT
public:
  struct HiveClientBuffer{
    QString buffer;
    int readSize = 0;
  };

  static bool decodeTcp(const QString &data, HiveClientBuffer *clientBuffer);
  static bool decodeUdp(const QString &data, const char *addr);
  static bool writeTcp(const MessageType &msgType, const QString &data);


protected:
  static inline bool decodeHivePacket(const QString &data, const QString &addr = "");

  bool processHeartBeat(const UsrProfileStruct &usrProfileStruct);
  bool processUsrLeave(QString *usrKey);
  bool processErrorDelivery();
  bool processTextMessage();
  bool processFileInfo();
  bool processFileContent();
  bool processFileAccept();
  bool processFileReject();

  static QByteArray encodeHeartBeat();
  static QByteArray encodeTextMessage(const QJsonObject &msg);

signals:
  void usrEntered(const UsrProfileStruct &usr);


};

#endif // HIVEPROTOCOL_H
