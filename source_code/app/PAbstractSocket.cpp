#include "PAbstractSocket.h"

void PAbstractSocket::bindCb(const PAbstractSocket::SockDestroyedCb &cb)
{
  destroyed_cb = cb;
}

void PAbstractSocket::bindCb(const SockReadyReadCb &cb)
{
  ready_read_cb = cb;
}

void PAbstractSocket::callDestroyed(const int &sockDescriptor)
{
  destroyed_cb(sockDescriptor);
}

void PAbstractSocket::callReadyRead(char *data, char *ip)
{
  ready_read_cb(data, ip);

}

void PAbstractSocket::write(uv_stream_t *handle, ssize_t nread, const uv_buf_t *buf)
{

}

void PAbstractSocket::bind(const char *ipAddr, const int &port)
{

}

void PAbstractSocket::start()
{

}

void PAbstractSocket::stop()
{

}

void PAbstractSocket::allocBuffer(uv_handle_t *handle, size_t suggestedSize, uv_buf_t *buf)
{
  buf->base = (char*) malloc(suggestedSize);
  buf->len = suggestedSize;
}

int PAbstractSocket::getSocketDescriptor(uv_handle_t* handle)
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










