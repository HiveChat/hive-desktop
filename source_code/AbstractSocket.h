#ifndef ABSTRACTSOCKET_H
#define ABSTRACTSOCKET_H

#include <QObject>

#ifdef Q_OS_WIN
#include "../dependency/win32/libuv/include/uv.h"
#else
#include <uv.h>
#endif

class AbstractSocket
{
  typedef int SocketDescriptor;
public:
//  virtual static void write(uv_stream_t *handle, ssize_t nread, const uv_buf_t *buf);

protected:
//  static int getSocketDescriptor();



};

#endif // ABSTRACTSOCKET_H
