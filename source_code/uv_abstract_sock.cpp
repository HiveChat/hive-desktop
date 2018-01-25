#include "uv_abstract_sock.h"

void UvAbstractSock::bindCb(const UvAbstractSock::SockDestroyedCb &cb)
{
  destroyed_cb = cb;
}

void UvAbstractSock::bindCb(const SockReadyReadCb &cb)
{
  ready_read_cb = cb;
}

void UvAbstractSock::callDestroyed(const int &sockDescriptor)
{
  destroyed_cb(sockDescriptor);
}

void UvAbstractSock::callReadyRead(char *data, char *ip)
{
  ready_read_cb(data, ip);

}

void UvAbstractSock::write(uv_stream_t *handle, ssize_t nread, const uv_buf_t *buf)
{

}

void UvAbstractSock::bind(const char *ipAddr, const int &port)
{

}

void UvAbstractSock::start()
{

}

void UvAbstractSock::stop()
{

}

void UvAbstractSock::allocBuffer(uv_handle_t *handle, size_t suggestedSize, uv_buf_t *buf)
{
  buf->base = (char*) malloc(suggestedSize);
  buf->len = suggestedSize;
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

//template void UvAbstractSock::bindCb<UvAbstractSock::SockReadyReadCb>(UvAbstractSock::Callback, UvAbstractSock::SockReadyReadCb);

//template<typename T>
//void UvAbstractSock::bindCb(Callback cbType, T cb)
//{
//  switch (cbType) {
//    case Callback::Read:
//      ready_read_cb = cb;
//      break;
//    default:
//      break;
//    }
//}










