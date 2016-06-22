#include "UserData.h"

UserData::UserData(const UsrProfileStruct *usr_profile_struct, QObject *parent) : QObject(parent)
{
  usr_key = usr_profile_struct->key_str;
  history_path = usr_path+usr_key;

  ThreadData::checkDir(history_path);


}
