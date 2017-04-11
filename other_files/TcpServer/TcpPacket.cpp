#include "TcpPacket.h"

TcpPacket::TcpPacket(const DataType &dataType, QObject *parent)
  : QObject(parent)
  , data_type(dataType)
{
  switch (dataType) {
    case File:
      {

        break;
      }

    case FileHead:
      {

        break;
      }
    default:
      break;
    }
}

void TcpPacket::setFileInfo()
{
}

QByteArray TcpPacket::getBuffer()
{
  return buffer;
}

QString TcpPacket::getMd5(const QByteArray &data)
{
  return QCryptographicHash::hash(data, QCryptographicHash::Md5);
}
