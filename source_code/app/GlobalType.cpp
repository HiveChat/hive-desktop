#include "GlobalType.h"

bool operator ==(const UsrProfileStruct &arg1, const UsrProfileStruct &arg2)
{
  if(arg1.key == arg2.key
     && arg1.ip == arg2.ip
     && arg1.name == arg2.name
     && arg1.avatar == arg2.avatar)
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

//bool Settings::operator ==(const Settings::SettingsStruct &arg1, const Settings::SettingsStruct &arg2)
//{
//  if(arg1.profile_avatar_str == arg2.profile_avatar_str
//     && arg1.profile_name_str == arg2.profile_name_str
//     && arg1.chat_bubble_color_i == arg2.chat_bubble_color_i
//     && arg1.chat_bubble_color_o == arg2.chat_bubble_color_o
//     && arg1.profile_key_str == arg2.profile_key_str)
//    {
//      return true;
//    }
//  else
//    {
//      return false;
//    }
//}
//bool Settings::operator !=(const Settings::SettingsStruct &arg1, const Settings::SettingsStruct &arg2)
//{
//  return !(arg1 == arg2);
//}
