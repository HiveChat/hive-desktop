#ifndef GLOBALDATA_H
#define GLOBALDATA_H
#include <QStringList>
#include <QDatetime>
#include <QFont>
#include <QColor>
#include <QStandardPaths>

class GlobalData
{
public:
  ///UI
  static QFont g_font;
  static QColor g_windowColor;
  static QColor g_alphaTabColor;
  static QColor g_tabColor;

  ///data
  static QString g_myKeyStr;
  static QString g_myNameStr;
  static QString g_avatarPathStr;

  ///net
  static QString g_localHostIP;

  ///other
  static QString g_currentTime();

};

#endif // GLOBALDATA_H
