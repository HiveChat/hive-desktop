#ifndef ABSTRACTSOCKET_H
#define ABSTRACTSOCKET_H

#include <uv.h>

class AbstractSocket
{
  typedef int SocketDescriptor;
public:
  virtual static void write(uv_stream_t *handle, ssize_t nread, const uv_buf_t *buf);

protected:
//  static int getSocketDescriptor();



};

#endif // ABSTRACTSOCKET_H
