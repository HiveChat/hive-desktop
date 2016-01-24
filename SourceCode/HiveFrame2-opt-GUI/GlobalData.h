#ifndef GLOBALDATA_H
#define GLOBALDATA_H
#include <QStringList>
#include <QDatetime>
#include <QFont>
#include <QStandardPaths>

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

#endif // GLOBALDATA_H
