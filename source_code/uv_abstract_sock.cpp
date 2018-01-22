#include "uv_abstract_sock.h"

void UvAbstractSock::write(uv_stream_t *handle, ssize_t nread, const uv_buf_t *buf)
{

}

void UvAbstractSock::bind(const char *ipAddr, const int &port)
{

}

void UvAbstractSock::allocBuffer(uv_handle_t *handle, size_t suggestedSize, uv_buf_t *buf)
{
  buf->base = (char*) malloc(suggestedSize);
  buf->len = suggestedSize;
}

void UvAbstractSock::bindReadyReadCb(const UvAbstractSock::SockReadyReadCb &cb)
{
  ready_read_cb = cb;
}

int UvAbstractSock::getSocketDescriptor(uv_handle_t* handle)
{
  int fd;
#ifdef Q_OS_WIN
  uv_fileno(handle, (uv_os_fd_t*)(&fd));
#else
  uv_fileno(handle, &fd);
#endif
  return fd;
}



template<class T>
void UvAbstractSock::bindCb(Callback cbType, T cb)
{
  switch (cbType) {
    case Callback::Destryed:
      ready_read_cb = cb;
      break;
    default:
      break;
    }
}













