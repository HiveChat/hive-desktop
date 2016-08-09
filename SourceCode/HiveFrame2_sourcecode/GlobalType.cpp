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


bool operator ==(const SettingStruct &arg1, const SettingStruct &arg2)
{
  if(arg1.avatar_str == arg2.avatar_str
     && arg1.name_str == arg2.name_str
     && arg1.chat_bubble_color_i == arg2.chat_bubble_color_i
     && arg1.chat_bubble_color_o == arg2.chat_bubble_color_o
     && arg1.key_str == arg2.key_str)
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
