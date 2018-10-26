#ifndef GLOBALTYPE_H
#define GLOBALTYPE_H

#include <PBuffer.h>

#include <QString>
#include <QColor>
#include <QJsonObject>

namespace GUI
{
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
    Default = 0,
    Doc = 1,
    Exe = 2,
    Ppt = 3,
    Rar = 4,
    Txt = 5,
    Xls = 6,
    Zip = 7
  };
}

struct UsrProfile
{
  QString key;
  QString name;
  QString avatar;
  QString ip = "Offline";
  bool online = false;
};
bool operator !=(const UsrProfile &arg1 , const UsrProfile &arg2);
bool operator ==(const UsrProfile &arg1 , const UsrProfile &arg2);

struct UpdateStruct
{
  int version[3];
  QString message;
  QString title;
};

namespace Settings
{
  struct Notification
  {
    bool update_notification;
    bool message_notification;
    bool message_detail_notification;
  };

  struct Update
  {
    bool auto_check_update;
    bool auto_update;
  };

  struct SettingsStruct
  {
    bool modified;

    int window_width;
    int window_height;

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

enum BaseProtocol{
  Any = 0,
  Udp = 1,
  Tcp = 2
};

struct NetPacket {
  NetPacket(std::string ip, Parsley::Buffer* buf, const BaseProtocol &protocol)
    : ip_addr(ip)
    , buffer(buf)
    , protocol(protocol)
  {

  }

  NetPacket(std::string ip, char* data, const int &len, const BaseProtocol &protocol)
    : ip_addr(ip)
    , protocol(protocol)
  {
    buffer = new Parsley::Buffer(data, len, Parsley::Loop::defaultLoop());
  }

  ~NetPacket()
  {
    delete[] buffer;
    buffer = nullptr;
  }

  std::string ip_addr;
  Parsley::Buffer* buffer;
  BaseProtocol protocol;


};


#endif // GLOBALTYPE_H
