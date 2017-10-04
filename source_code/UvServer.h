#ifndef UVTCPSERVER_H
#define UVTCPSERVER_H

#define UDP_PORT 23232

#define TCP_PORT 23232
#define TCP_BACKLOG 128

#include "HiveProtocol.h"

#include <QThread>
#include <QDebug>
#include <QHash>

#ifdef Q_OS_WIN
#include "../dependency/win32/libuv/include/uv.h"
#else
#include <uv.h>
#endif

class UvServer;


class UvServer
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
  explicit UvServer(QObject *parent = 0);
  ~UvServer();

  void write();
  void quit();

protected:
  void run();

private:  
  static uv_loop_t *loop;

  static QHash<SocketDescriptor, HiveProtocol::HiveClient*> buffer_hash;
  static QHash<QString, SocketDescriptor> key_sd_hash;

  inline static void udpRead(uv_udp_t *req, ssize_t nread, const uv_buf_t *buf, const sockaddr *addr, unsigned flags);
  inline static void udpWrite();
  inline static void tcpNewConnection(uv_stream_t *server, int status);
  inline static void tcpRead(uv_stream_t *client, ssize_t nread, const uv_buf_t *buf);
  inline static void tcpWriten(uv_write_t *req, int status);

  inline static void allocBuffer(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf);
  inline static void freeWriteReq(uv_write_t *req);



  inline static int getSocketDescriptor(uv_stream_t *client);

};

#endif // UVTCPSERVER_H
