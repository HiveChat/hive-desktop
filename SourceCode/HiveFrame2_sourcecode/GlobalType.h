#ifndef GLOBALTYPE_H
#define GLOBALTYPE_H

#include <QString>
#include <QColor>

enum StaticStackType
{
  NULL_Stack,
  Home_Welcome,
  Home_list,
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

enum BuiltInIconType
{
  doc,
  exe,
  ppt,
  rar,
  txt,
  xls,
  zip
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
  QString time_str;
};

struct FileInfoStruct
{
  QString name;
  QString size;
  QString type;
  bool direct_display;
};

namespace Settings {

  enum Notification{
    ShowCount,
    ShowDetail,
    None
  };

  struct SettingStruct
  {
    QColor chat_bubble_color_i;
    QColor chat_bubble_color_o;
    QString profile_avatar_str;
    QString profile_name_str;
    QString profile_key_str;
    Notification notification;
  };
  bool operator !=(const SettingStruct &arg1 , const SettingStruct &arg2);
  bool operator ==(const SettingStruct &arg1 , const SettingStruct &arg2);

}



#endif // GLOBALTYPE_H
