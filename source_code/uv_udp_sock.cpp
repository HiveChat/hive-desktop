#include "uv_udp_sock.h"

QHash<int, UvUdpSock*> UvUdpSockUtils::udp_sock_hash;

void
UvUdpSockUtils::receiveCb(uv_udp_t *handle, ssize_t nread, const uv_buf_t *buf, const sockaddr *addr, unsigned flags)
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
          Log::net(Log::Normal, "UvUdpSockUtils::read()", QString("UDP Packet Received From %1").arg(senderAddr));

          uv_buf_t buffer = uv_buf_init(buf->base, nread);
          qDebug()<<buffer.base;

          udp_sock_hash.value(UvAbstractSock::getSocketDescriptor((uv_handle_t*) handle))->callReadyRead(buffer.base, senderAddr);
          /// Do callback or what ever
        }
    }
  else
    {
      if(addr != NULL)
        {
          Log::net(Log::Normal, "UvUdpSockUtils::read()", "Empty UDP Packet Received...");
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






UvUdpSock::UvUdpSock(const char *ipAddr, const int &port, uv_loop_t *loop)
{
  uv_loop = loop;
  struct sockaddr_in *udpAddr = (sockaddr_in*)malloc(sizeof(sockaddr_in));
  uv_ip4_addr(ipAddr, port, udpAddr);
  udp_socket = (uv_udp_t*) malloc(sizeof(uv_udp_t));
  uv_udp_init(loop, udp_socket);
  uv_udp_bind(udp_socket, (const struct sockaddr*) udpAddr, UV_UDP_REUSEADDR);

  udp_sock_hash.insert(getSocketDescriptor((uv_handle_t*) udp_socket), this);

  uv_udp_recv_start(udp_socket, allocBuffer, receiveCb);
  uv_udp_set_broadcast(udp_socket, 1);

}

void
UvUdpSock::write(const char *ipAddr, const int &port, const uv_buf_t *buf)
{
  uv_udp_send_t *req = (uv_udp_send_t*)malloc(sizeof(uv_udp_send_t));
  struct sockaddr_in addr;
  uv_ip4_addr(ipAddr, port, &addr);
  uv_udp_send(req, udp_socket, buf, 1, (const struct sockaddr *)&addr, writeCb);

  Log::net(Log::Normal, "UvServer::sendTextMessage()", "message sent");
}

