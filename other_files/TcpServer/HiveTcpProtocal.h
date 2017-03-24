#ifndef HIVETCPPROTOCAL_H
#define HIVETCPPROTOCAL_H

#include <QObject>
#include <QJsonObject>
#include <QJsonDocument>
#include <QByteArray>
#include <QDebug>
#include <QCryptographicHash>


class HiveTcpProtocal : public QObject
{
  Q_OBJECT

  enum DataType {
    FileHead,
    File,
    FileEnd,
  };


public:
  explicit HiveTcpProtocal(const DataType &dataType, QObject *parent = 0);

  void setFileInfo();
  QByteArray getBuffer();

private:
  int buffer_size;
  QByteArray buffer;
  QJsonObject buffer_json_obj;

  DataType data_type;

  QString getMd5(const QString &data);

};

#endif // HIVETCPPROTOCAL_H
