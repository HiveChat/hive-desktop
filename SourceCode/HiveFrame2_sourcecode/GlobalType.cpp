#include "GlobalType.h"

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


bool Settings::operator ==(const Settings::SettingStruct &arg1, const Settings::SettingStruct &arg2)
{
  if(arg1.profile_avatar_str == arg2.profile_avatar_str
     && arg1.profile_name_str == arg2.profile_name_str
     && arg1.chat_bubble_color_i == arg2.chat_bubble_color_i
     && arg1.chat_bubble_color_o == arg2.chat_bubble_color_o
     && arg1.profile_key_str == arg2.profile_key_str)
    {
      return true;
    }
  else
    {
      return false;
    }
}
bool Settings::operator !=(const Settings::SettingStruct &arg1, const Settings::SettingStruct &arg2)
{
  return !(arg1 == arg2);
}
