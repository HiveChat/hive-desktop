#ifndef MESSAGE_H
#define MESSAGE_H

#include <QString>


enum MessageType {
  Null = 0,
  HeartBeat = 1,
  UsrLeave = 2,
  ErrorDelivery = 10,
  TextMessage = 20,
  PhotoMessage = 21,
  VideoMessage = 22,
  FileInfo = 30,
  FileContent = 31,
  FileAccept = 32,
  FileReject = 33,

};

struct HiveHeartBeat{
  QString receiver;
  QString sender;
  int time;
};

namespace Message {
  struct TextMessage{
    int index;
    QString reciever;
    QString sender;
    QString message;
    int time;
  };

  struct FileInfo{
    int index;
    QString reciever;
    QString sender;
    QByteArray md5;
    QString name;
    int size;
  };

  struct FileContent{
    int index;
    QString reciever;
    QString sender;
    QByteArray md5;
    QString content;
  };

  struct FileAccept{
    int index;
    QString reciever;
    QString sender;
    QByteArray md5;
  };

  struct FileReject{
    int index;
    QString reciever;
    QString sender;
    QByteArray md5;
    int reason;
  };

  struct ErrorDelivery{
    int index;
    QString reciever;
    QString sender;
    // << Build Protocol
  };
}



//class Message
//{
//public:
//  Message();
//};

#endif // MESSAGE_H
