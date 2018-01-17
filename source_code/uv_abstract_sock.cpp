#include "uv_abstract_sock.h"


void
UvAbstractSock::write(uv_stream_t *handle, ssize_t nread, const uv_buf_t *buf)
{

}

void
UvAbstractSock::allocBuffer(uv_handle_t *handle, size_t suggestedSize, uv_buf_t *buf)
{
  buf->base = (char*) malloc(suggestedSize);
  buf->len = suggestedSize;
}

int
UvAbstractSock::getSocketDescriptor(uv_handle_t* handle)
{
  int fd;
#ifdef Q_OS_WIN
  uv_fileno(handle, (uv_os_fd_t*)(&fd));
#else
  uv_fileno(handle, &fd);
#endif
  return fd;
}


