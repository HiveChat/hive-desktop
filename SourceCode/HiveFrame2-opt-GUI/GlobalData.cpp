#include "GlobalData.h"
#include <QPalette>


bool operator ==(const UsrProfileStruct &arg1, const UsrProfileStruct &arg2)
{
  if(arg1.key_str == arg2.key_str
     && arg1.ip_str == arg2.ip_str
     && arg1.name_str == arg2.name_str
     && arg1.avatar_str == arg2.avatar_str)
    {
      return true;
    }
  else
    {
      return false;
    }
}
bool operator !=(const UsrProfileStruct &arg1 , const UsrProfileStruct &arg2)
{
  return !(arg1 == arg2);
}


bool operator ==(const SettingStruct &arg1, const SettingStruct &arg2)
{
  if(arg1.avatar_path == arg2.avatar_path
     && arg1.usr_name == arg2.usr_name
     && arg1.chat_bubble_color_i == arg2.chat_bubble_color_i
     && arg1.chat_bubble_color_o == arg2.chat_bubble_color_o
     && arg1.usr_key == arg2.usr_key)
    {
      return true;
    }
  else
    {
      return false;
    }
}
bool operator !=(const SettingStruct &arg1, const SettingStruct &arg2)
{
  return !(arg1 == arg2);
}


///UI
QFont GlobalData::g_font;
QColor GlobalData::g_windowColor = QColor(255,255,255);
QColor GlobalData::g_alphaTabColor = QColor(255,255,255,240);
QColor GlobalData::g_tabColor = QColor(0,0,0,0);

QColor GlobalData::g_chatBubbleColorI = QColor(255,215,126);
QColor GlobalData::g_chatBubbleColorO = QColor(225,225,225);
QColor GlobalData::g_mChatBubbleColorI = GlobalData::g_chatBubbleColorI;
QColor GlobalData::g_mChatBubbleColorO = GlobalData::g_chatBubbleColorO;

///data
SettingStruct GlobalData::g_settings_struct;
UsrProfileStruct GlobalData::g_my_profile;
QMap<QString, UsrProfileStruct> GlobalData::saved_usr_profile_map;
QMap<QString, UsrProfileStruct> GlobalData::online_usr_profile_map;

///net
QString GlobalData::g_localHostIP;

QString GlobalData::g_currentTime()
{
  return QDateTime::currentDateTime().toString("yyyy_MM_dd_hh_mm_ss");
}


