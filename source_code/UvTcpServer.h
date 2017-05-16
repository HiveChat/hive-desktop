#ifndef UVTCPSERVER_H
#define UVTCPSERVER_H

#define TCP_PORT 23232
#define TCP_BACKLOG 128

#include "Log.h"
#include "HiveProtocol.h"
#include "UsrData.h"

#include <QThread>
#include <QDebug>
#include <QHash>

#include <uv.h>

class UvTcpServer;
class Bee;

class UvTcpServer : public QThread
{
  Q_OBJECT
public:
  explicit UvTcpServer(QObject *parent = 0);

protected:
  void run();

private:
  static HiveProtocol *hive_protocol;
  static uv_loop_t *loop;
  static struct sockaddr_in addr;

  static QHash<int, QByteArray> buffer_hash;
  static QHash<int, UsrData*> connection_hash;

  static void onNewConnection(uv_stream_t *server, int status);
  static void tcpRead(uv_stream_t *client, ssize_t nread, const uv_buf_t *buf);
  static void tcpWrite(uv_write_t *req, int status);
  static void allocBuffer(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf);
  static void freeWriteReq(uv_write_t *req);

  inline static int getSocketDescriptor(uv_stream_t *client);

  typedef struct {
    uv_write_t req;
    uv_buf_t buf;
  } write_req_t;
};


class Bee
{
public:
  explicit Bee(const int &socketDiscriptor);

  bool readBuffer(const QString &buffer);

  bool isLeaving();
  bool isIdentified();

private:
  int socket_descriptor;
  UsrData *usr_data = nullptr;
  QString buffer;

  bool is_leaving;

};

#endif // UVTCPSERVER_H
