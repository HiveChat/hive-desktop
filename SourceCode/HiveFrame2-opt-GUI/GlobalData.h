#ifndef GLOBALDATA_H
#define GLOBALDATA_H
#include <QStringList>
#include <QDatetime>
#include <QFont>
#include <QMap>
#include <QColor>
#include <QStandardPaths>


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

struct UsrProfileStruct
{
  QString key_str;
  QString name_str;
  QString avatar_str;
  QString ip_str = "Offline";
};
bool operator !=(const UsrProfileStruct &arg1 , const UsrProfileStruct &arg2);
bool operator ==(const UsrProfileStruct &arg1 , const UsrProfileStruct &arg2);

struct MessageStruct
{
  QString reciever_key;
  QString sender_key;
  QString message_str;
};

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
  static UsrProfileStruct g_my_profile;
  static QMap<QString, UsrProfileStruct> saved_usr_profile_map;
  static QMap<QString, UsrProfileStruct> online_usr_profile_map;

  ///net
  static QString g_localHostIP;

  ///other
  static QString g_currentTime();

};




#endif // GLOBALDATA_H
