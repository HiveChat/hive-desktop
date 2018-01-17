#include "uv_udp_sock_utils.h"


bool UvUdpSockUtils::keep_alive;

void
UvUdpSockUtils::read(uv_udp_t *handle, ssize_t nread, const uv_buf_t *buf, const sockaddr *addr, unsigned flags)
{
  /// DOC: libuv 1.18.1-dev
  ///  - The receive callback will be called with nread == 0 and addr == NULL when there is nothing to read,
  ///  - and with nread == 0 and addr != NULL when an empty UDP packet is received.
  if(nread != 0)
    {
      if(addr != NULL)
        {
          char senderAddr[17] = { 0 };
          uv_ip4_name((const struct sockaddr_in*)addr, senderAddr, 16);
          Log::net(Log::Normal, "UdpSocket::udpReadCb()", QString("Recv from %1").arg(senderAddr));

          uv_buf_t buffer = uv_buf_init(buf->base, nread);
          qDebug()<<buffer.base;
          /// Do callback or what ever
        }
    }
  else
    {
      if(addr != NULL)
        {
          Log::net(Log::Normal, "UdpSocket::udpReadCb()", "Empty Packet Received...");
        }
      if(!keep_alive)
        {
          uv_close((uv_handle_t*) handle, NULL);
        }
    }

  free(buf->base);
  return;
}

void
UvUdpSockUtils::writeCb(uv_udp_send_t *req, int status)
{
  free(req);
}

void
UvUdpSockUtils::allocBuffer(uv_handle_t *handle, size_t suggestedSize, uv_buf_t *buf)
{
  buf->base = (char*) malloc(suggestedSize);
  buf->len = suggestedSize;
}


