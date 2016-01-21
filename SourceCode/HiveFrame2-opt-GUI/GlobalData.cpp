#include "GlobalData.h"

///data
QString GlobalData::g_myKeyStr;
QString GlobalData::g_myNameStr;
QString GlobalData::g_avatarPathStr;

///net
QString GlobalData::g_localHostIP;

QString GlobalData::g_currentTime()
{
  QDateTime::currentDateTime().toString("yyyy_MM_dd_hh_mm_ss");
}




////////Data Standard:////////
/*
usrInfoStrList:
usrKey<<usrName<<ipAddr<<avatarPath

myProfile:
usrKey<<usrName<<avatarPath


*/
