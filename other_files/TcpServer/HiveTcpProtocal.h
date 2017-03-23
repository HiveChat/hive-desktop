#ifndef HIVETCPPROTOCAL_H
#define HIVETCPPROTOCAL_H

#include <QObject>
#include <QJsonObject>
#include <QJsonDocument>
#include <QByteArray>
#include <QDebug>


class HiveTcpProtocal : public QObject
{
  Q_OBJECT

  enum DataType {
    FileHead,
    File,
    FileEnd,
  };

public:
  explicit HiveTcpProtocal(QObject *parent = 0);

private:
  int buffer_size;
  QByteArray buffer;
  QJsonObject buffer_json_obj;

  DataType data_type;

};

#endif // HIVETCPPROTOCAL_H
