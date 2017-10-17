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
    TextMessage = 20,
    PhotoMessage = 21,
    VideoMessage = 22,
    FileInfo = 30,
    FileContent = 31,
    FileAccept = 32,
    FileReject = 33,
  };


public:
  enum BaseProtocol{
    Any = 0,
    Udp = 1,
    Tcp = 2
  };

  struct HiveClient{
    QString buffer;
    int readSize = 0;
  };

  struct HiveHeartBeat{
    QString receiver;
    QString sender;
    int time;
  };

  struct HiveTextMessage{
    int index;
    QString reciever;
    QString sender;
    QString message;
    int time;
  };

  struct HiveFileInfo{
    int index;
    QString reciever;
    QString sender;
    QString name;
    QByteArray md5;
    int size;
  };

  struct HiveFileContent{
    int index;
    QString reciever;
    QString sender;
    QString content;
    QByteArray md5;
  };

  struct HiveFileAccept{
    int index;
    QString reciever;
    QString sender;
    QByteArray md5;
  };

  struct HiveFileReject{
    int index;
    QString reciever;
    QString sender;
    QByteArray md5;
    int reason;
  };

  struct HiveErrorDelivery{
    int index;
    QString reciever;
    QString sender;
    // << Build Protocol
  };


  static bool readTcp(const QString &data, HiveClient *clientBuffer);
  static bool writeTcp(const HiveProtocol::MessageType &MsgType, const QString &data);


protected:

  static inline bool decodeHivePacket(const QString &data);
  static inline bool processHeartBeat(const UsrProfileStruct &usrProfileStruct);
  static inline bool processUsrLeave(QString *usrKey);
  static inline bool processErrorDelivery();
  static inline bool processTextMessage();
  static inline bool processFileInfo();
  static inline bool processFileContent();
  static inline bool processFileAccept();
  static inline bool processFileReject();

  static QByteArray makeHeartBeat();


//using inheritance, not private variables in theory, leave the error until private data is fully separated.
//  int socket_descriptor;
//  uv_stream_t *tcp_handle;
//  UsrData *usr_data = nullptr;
//  QString buffer;
//  int read_size = 0;
//  bool is_leaving;


};

#endif // HIVEPROTOCOL_H
