#ifndef GLOBALDATA_H
#define GLOBALDATA_H
#include <QStringList>
#include <QDatetime>
#include <QFont>

class GlobalData
{
public:
  ///data
  static QString g_myKeyStr;
  static QString g_myNameStr;
  static QString g_avatarPathStr;
  static QFont g_font;

  //static QJsonObject

  ///net
  static QString g_localHostIP;

  ///other
  static QString g_currentTime();

};

struct a
{

};

#endif // GLOBALDATA_H
