#include "HiveTcpProtocal.h"

HiveTcpProtocal::HiveTcpProtocal(const DataType &dataType, QObject *parent)
  : QObject(parent)
  , data_type(dataType)
{
  switch (dataType) {
    case File:
      {

        break;
      }
    case FileEnd:
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

void HiveTcpProtocal::setFileInfo()
{
}

QByteArray HiveTcpProtocal::getBuffer()
{
  return buffer;
}

QString HiveTcpProtocal::getMd5(const QString &data)
{
  return QCryptographicHash::hash(data, QCryptographicHash::Md5);
}
