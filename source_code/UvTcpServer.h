#ifndef UVTCPSERVER_H
#define UVTCPSERVER_H

#define TCP_PORT 23232
#define TCP_BACKLOG 128

#define UDP_PORT 23232

#include "Log.h"
#include "UsrData.h"
#include "GlobalData.h"

#include <QThread>
#include <QDebug>
#include <QHash>

#ifdef Q_OS_WIN
#include "../dependency/win32/libuv/include/uv.h"
#else
#include <uv.h>
#endif

class HiveProtocol;
class UvTcpServer;

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

class UvTcpServer
    : public QThread
    , public HiveProtocol
{
  Q_OBJECT

  typedef int SocketDescriptor;
  typedef struct {
    uv_write_t req;
    uv_buf_t buf;
  } write_req_t;

public:
  explicit UvTcpServer(QObject *parent = 0);
  ~UvTcpServer();

  void closeUvLoop();

protected:
  void run();

private:  
  static uv_loop_t *loop;
  static struct sockaddr_in addr;

  static QHash<SocketDescriptor, HiveProtocol::HiveClient*> buffer_hash;
  static QHash<QString, SocketDescriptor> key_sd_hash;

  inline static void onNewConnection(uv_stream_t *server, int status);
  inline static void tcpRead(uv_stream_t *client, ssize_t nread, const uv_buf_t *buf);
  inline static void tcpWrite(uv_write_t *req, int status);
  inline static void allocBuffer(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf);
  inline static void freeWriteReq(uv_write_t *req);

  inline static int getSocketDescriptor(uv_stream_t *client);

};

#endif // UVTCPSERVER_H
