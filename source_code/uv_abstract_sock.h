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
public:
  enum Callback {
    Destryed = 0,
    Read = 1,
    Written = 2
  };

  typedef int SocketDescriptor;
  typedef std::function<void (char*, char*)> SockReadyReadCb;

  virtual void bindReadyReadCb(const SockReadyReadCb &cb);

  template <class T>
  void bindCb(Callback cbType, T cb);


  static int getSocketDescriptor(uv_handle_t *handle);
  SockReadyReadCb ready_read_cb;

protected:
  int port;
  uv_loop_t* uv_loop;

  virtual void write(uv_stream_t *handle, ssize_t nread, const uv_buf_t *buf);
  virtual void bind(const char* ipAddr, const int &port);

  static void allocBuffer(uv_handle_t *handle, size_t suggestedSize, uv_buf_t *buf);
};

#endif // ABSTRACTSOCKET_H
