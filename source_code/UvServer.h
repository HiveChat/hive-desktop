#ifndef UVTCPSERVER_H
#define UVTCPSERVER_H

#define UDP_PORT 23232

#define TCP_PORT 23232
#define TCP_BACKLOG 128

#include "HiveProtocol.h"
#include "UdpSocket.h"
#include "TcpServer.h"

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
  static TcpServer *tcp_server;
  static UdpSocket *udp_server;
  static uv_timer_t *heart_beat_timer;

  static QHash<SocketDescriptor, HiveProtocol::HiveClientBuffer*> buffer_hash;
  static QHash<QString, SocketDescriptor> key_sd_hash;

  static void uvWalkCb(uv_handle_t* handle, void* arg);
  static void uvCloseCb(uv_handle_t* handle);

  static void udpHeartBeatCb(uv_timer_t *handle);

//  static void tcpNewConnectionCb(uv_stream_t *handle, int status);
//  static void tcpReadCb(uv_stream_t *handle, ssize_t nread, const uv_buf_t *buf);
//  static void tcpWriteCb(uv_write_t *handle, int status);
//  static void udpReadCb(uv_udp_t *handle, ssize_t nread, const uv_buf_t *buf, const sockaddr *addr, unsigned flags);
//  static void udpWriteCb(uv_udp_send_t *handle, int status);


//  static void allocBuffer(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf);
//  static void freeWriteReq(uv_write_t *handle);

//  static int getSocketDescriptor(uv_handle_t *handle);

  /// BEGIN: 9 Dec. 2017 Test
  ///  - GitHub Source: ultrasilicon/uv_tcp_echo.c
  ///  - URL: https://gist.github.com/ultrasilicon/f070f7acc4fe0b036d37f9383a484f5c
//  static bool stop;
//  static struct sockaddr_in addr;
//  static void on_new_connection(uv_stream_t *server, int status);
//  static void alloc_buffer(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf);
//  static void echo_read(uv_stream_t *client, ssize_t nread, const uv_buf_t *buf);
//  static void echo_write(uv_write_t *req, int status);
//  static void free_write_req(uv_write_t *req);
//  static void timer_cb(uv_timer_t *handle);
//  static void timer_cb2(uv_timer_t *handle);
  /// END: 9 Dec. 2017 Test



};

#endif // UVTCPSERVER_H
