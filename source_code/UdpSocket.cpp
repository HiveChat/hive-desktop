#include "UdpSocket.h"

bool UdpSocket::keep_alive;
uv_udp_t* UdpSocket::uv_udp_socket;
uv_loop_t* UdpSocket::uv_loop;


UdpSocket::UdpSocket(const char *ipAddr, const int &port, uv_loop_t *loop)
{
  uv_loop = loop;
  struct sockaddr_in *udpAddr = (sockaddr_in*)malloc(sizeof(sockaddr_in));
  uv_ip4_addr(ipAddr, port, udpAddr);
  uv_udp_socket = (uv_udp_t*) malloc(sizeof(uv_udp_t));
  uv_udp_init(loop, uv_udp_socket);
  uv_udp_bind(uv_udp_socket, (const struct sockaddr*) udpAddr, UV_UDP_REUSEADDR);
  uv_udp_recv_start(uv_udp_socket, allocBuffer, udpReadCb);
  uv_udp_set_broadcast(uv_udp_socket, 1);
}

void UdpSocket::udpReadCb(uv_udp_t *handle, ssize_t nread, const uv_buf_t *buf, const sockaddr *addr, unsigned flags)
{
  if(nread >= 0 && addr) //addr sometimes is a nullptr
    {
      char senderAddr[17] = { 0 };
      uv_ip4_name((const struct sockaddr_in*)addr, senderAddr, 16);
      Log::net(Log::Normal, "UdpSocket::udpReadCb()", "Recv from %s\n" + QString(senderAddr));

      uv_buf_t buffer = uv_buf_init(buf->base, nread);
      /// Do callback or what ever
    }
  else
    {
      fprintf(stderr, "UDP Read error %s\n", uv_err_name(nread));
      if(!keep_alive)
        {
          uv_close((uv_handle_t*) handle, NULL);
        }
    }

  free(buf->base);
  return;
}

void UdpSocket::allocBuffer(uv_handle_t *handle, size_t suggestedSize, uv_buf_t *buf)
{
  buf->base = (char*) malloc(suggestedSize);
  buf->len = suggestedSize;
}
