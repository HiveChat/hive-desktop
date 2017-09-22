#ifndef HIVEPROTOCOL_H
#define HIVEPROTOCOL_H

#include "Log.h"
#include "UsrData.h"
#include "GlobalData.h"

class HiveProtocol
{
  enum MessageType {
    HeartBeat = 0,
    UsrLeave = 1,
    ErrorDelivery = 10,
    Message = 20,
    FileInfo = 30,
    FileContent = 31,
    FileAccept = 32,
    FileReject = 33,
  };



public:
  struct TextMessageStruct{
    QString index;
    QString reciever;
    QString sender;
    QString message;
    QString time;
  };

  struct HiveClient{
    QString buffer;
    int readSize = 0;
  };

  static bool readTcp(const QString &data, HiveClient *clientBuffer);
  static bool writeTcp(const HiveProtocol::MessageType &MsgType, const QString &data);

private:

  static inline bool decodePacket(const QString &data);
  static inline bool processHeartBeat(const UsrProfileStruct &usrProfileStruct);
  static inline bool processUsrLeave(QString *usrKey);
  static inline bool processErrorDelivery();
  static inline bool processMessage();
  static inline bool processFileInfo();
  static inline bool processFileContent();
  static inline bool processFileAccept();
  static inline bool processFileReject();


//using inheritance, not private variables in theory, leave the error until private data is fully separated.
//  int socket_descriptor;
//  uv_stream_t *tcp_handle;
//  UsrData *usr_data = nullptr;
//  QString buffer;
//  int read_size = 0;
//  bool is_leaving;


};

#endif // HIVEPROTOCOL_H
