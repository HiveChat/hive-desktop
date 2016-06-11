#ifndef GLOBALDATA_H
#define GLOBALDATA_H

#include <QDate>
#include <QFont>
#include <QMap>
#include <QPalette>
#include <QColor>
#include <QStandardPaths>


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

struct SettingStruct
{
  QColor chat_bubble_color_i;
  QColor chat_bubble_color_o;
  QString avatar_str;
  QString key_str;
  QString name_str;
};
bool operator !=(const SettingStruct &arg1 , const SettingStruct &arg2);
bool operator ==(const SettingStruct &arg1 , const SettingStruct &arg2);

class GlobalData
{
public:
  ///UI
  static QFont font_futura;
  static QFont font_chatTextEditor;
  static QFont font_chatBubble;
  static QFont font_combWidgetUsrName;
  static QFont font_combWidgetIpAddr;
  static QFont font_menuButton;
  static QFont font_scrollStackTitle;
  static QFont font_scrollStackSubtitle;

  //!base color
  static QColor bc_darkGrey;
  static QColor bc_lightGrey;
  static QColor bc_brown;
  static QColor bc_hiveYellow;
  static QColor bc_lightYellow;

  static QColor color_window;
  static QColor color_alphaTab;
  static QColor color_tab;

  static QColor color_defaultChatBubbleI;
  static QColor color_defaultChatBubbleO;
  static QColor color_mChatBubbleI;
  static QColor color_mChatBubbleO;

  static QPalette palette_bkg_normalWhite;
  static QPalette palette_bkg_transparent;
  static QPalette palette_txt_brown;

  ///data
  static QString g_version[3];
  static SettingStruct g_settings_struct;
  static QMap<QString, UsrProfileStruct> saved_usr_profile_map;
  static QMap<QString, UsrProfileStruct> online_usr_profile_map;

  ///net
  static QString g_localHostIP;

  ///other
  static QString g_currentTime();

};




#endif // GLOBALDATA_H
