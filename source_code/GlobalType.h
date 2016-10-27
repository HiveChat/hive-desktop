#ifndef GLOBALTYPE_H
#define GLOBALTYPE_H

#include <QString>
#include <QColor>
#include <QJsonObject>

enum StaticStackType
{
  NULL_Stack,
  Home_Welcome,
  Home_list,
  Home_Storage,
  Settings_Messaging,
  Settings_Profile,
  Settings_Style,
  Settings_Questions,
  Settings_Update
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
  struct Notification{
    bool update_notification;
    bool message_notification;
    bool message_detail_notification;
  };

  struct Update{
    bool auto_check_update;
    bool auto_update;
    QJsonObject update_json;
  };

  struct SettingsStruct
  {
    bool modified_lock;
    QColor chat_bubble_color_i;
    QColor chat_bubble_color_o;

    QString profile_avatar_str;
    QString profile_name_str;
    QString profile_key_str;

    Notification notification;
    Update update;
  };
//  bool operator !=(const SettingsStruct &arg1 , const SettingsStruct &arg2);
//  bool operator ==(const SettingsStruct &arg1 , const SettingsStruct &arg2);

}



#endif // GLOBALTYPE_H
