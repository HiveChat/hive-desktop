#ifndef UV_UDP_SOCK_UTILS_H
#define UV_UDP_SOCK_UTILS_H

#include "Log.h"

#ifdef Q_OS_WIN
#include "../dependency/win32/libuv/include/uv.h"
#else
#include <uv.h>
#endif

class UvUdpSockUtils
{
protected:
  static bool keep_alive;

  static void read(uv_udp_t *handle, ssize_t nread, const uv_buf_t *buf, const sockaddr *addr, unsigned flags);
  static void writeCb(uv_udp_send_t* req, int status);
  static void allocBuffer(uv_handle_t *handle, size_t suggestedSize, uv_buf_t *buf);


};

#endif // UV_UDP_SOCK_UTILS_H
