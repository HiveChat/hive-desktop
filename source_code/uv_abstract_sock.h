#ifndef ABSTRACTSOCKET_H
#define ABSTRACTSOCKET_H

#include "Log.h"

#ifdef Q_OS_WIN
#include "../dependency/win32/libuv/include/uv.h"
#else
#include <uv.h>
#endif


class UvAbstractSock
{
  typedef int SocketDescriptor;
public:

protected:
  virtual void write(uv_stream_t *handle, ssize_t nread, const uv_buf_t *buf);

  static void allocBuffer(uv_handle_t *handle, size_t suggestedSize, uv_buf_t *buf);
  static int getSocketDescriptor(uv_handle_t *handle);





};

#endif // ABSTRACTSOCKET_H
