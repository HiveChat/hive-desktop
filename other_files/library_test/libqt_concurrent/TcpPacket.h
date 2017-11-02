#ifndef HIVETCPPROTOCAL_H
#define HIVETCPPROTOCAL_H

#include <QObject>
#include <QJsonObject>
#include <QJsonDocument>
#include <QByteArray>
#include <QDebug>
#include <QCryptographicHash>


class TcpPacket : public QObject
{
  Q_OBJECT

  enum DataType {
    FileHead,
    File
  };


public:
  explicit TcpPacket(const DataType &dataType, QObject *parent = 0);

  void setFileInfo();
  QByteArray getBuffer();

private:
  int buffer_size;
  QByteArray buffer;
  QJsonObject buffer_json_obj;

  DataType data_type;

  QString getMd5(const QByteArray &data);

};

#endif // HIVETCPPROTOCAL_H
