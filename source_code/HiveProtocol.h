#ifndef HIVEPROTOCOL_H
#define HIVEPROTOCOL_H

#include <QObject>
#include <QHash>

class HiveProtocol
{
public:
  explicit HiveProtocol();

  static void append(const QByteArray &data, const int &socketDiscriptor, QHash<int, QByteArray> *hash);
  static void decodeContent();
};

#endif // HIVEPROTOCOL_H
