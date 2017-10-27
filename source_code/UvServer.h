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

  void quit();

  void sendTextMessage(const QJsonObject &msg, const BaseProtocol &protocol = BaseProtocol::Udp);

protected:
  void run();

private:  
  static uv_loop_t *loop;
  static uv_tcp_t *tcp_server;
  static uv_udp_t *udp_server;

  static QHash<SocketDescriptor, HiveProtocol::HiveClient*> buffer_hash;
  static QHash<QString, SocketDescriptor> key_sd_hash;

  static void udpReadCb(uv_udp_t *handle, ssize_t nread, const uv_buf_t *buf, const sockaddr *addr, unsigned flags);
  static void udpWrite();
  static void tcpNewConnection(uv_stream_t *handle, int status);
  static void tcpReadCb(uv_stream_t *handle, ssize_t nread, const uv_buf_t *buf);
  static void tcpWriten(uv_write_t *handle, int status);

  static void udpHeartBeatCb(uv_timer_t *handle);
  static void udpWriten(uv_udp_send_t *req, int status);

  static void allocBuffer(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf);
  static void freeWriteReq(uv_write_t *handle);


  static int getSocketDescriptor(uv_handle_t *client);


};

#endif // UVTCPSERVER_H
