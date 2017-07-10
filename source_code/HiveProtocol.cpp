#include "HiveProtocol.h"

HiveProtocol::HiveProtocol()
{

}

void HiveProtocol::append(const QByteArray &data, const int &socketDiscriptor, QHash<int, QByteArray> *hash)
{
  if(hash->contains(socketDiscriptor))
    {
//      hash->value(socketDiscriptor).append(data);
    }
  else
    {
      hash->insert(socketDiscriptor, data);
    }


//  QByteArray *stream = hash->value(socketDiscriptor);
//  if(stream->size() == stream->mid(0, 31).toInt() + 32)
//    {

//    }

}
