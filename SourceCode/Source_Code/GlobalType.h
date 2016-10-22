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

namespace Message {
  enum MessageType{
    TextMessage,
    FileInfo
  };

  struct TextMessageStruct
  {
    QString index;
    QString reciever;
    QString sender;
    QString message;
    QString time;
  };

  struct FileInfoStruct
  {
    QString index;
    QString name;
    QString size;
    QString type;
  };

}

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
