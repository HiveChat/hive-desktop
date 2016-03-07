#ifndef GLOBALDATA_H
#define GLOBALDATA_H
#include <QStringList>
#include <QDatetime>
#include <QFont>
#include <QMap>
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

  static QColor g_chatBubbleColorI;
  static QColor g_chatBubbleColorO;
  static QColor g_mChatBubbleColorI;
  static QColor g_mChatBubbleColorO;


  ///data
  static QString g_myKeyStr;
  static QString g_myNameStr;
  static QString g_avatarPathStr;

  ///net
  static QString g_localHostIP;

  ///other
  static QString g_currentTime();

};

enum StaticStackType
{
  NULL_Stack,
  Home_Welcome,
  Home_Storage,
  Settings_Messaging,
  Settings_Profile,
  Settings_Style,
  Settings_Questions
};

enum BuiltInAvatarType
{
  Bee,
  Disk,
  Fat,
  Ladybug,
  sunflower,
  worm
};


#endif // GLOBALDATA_H
