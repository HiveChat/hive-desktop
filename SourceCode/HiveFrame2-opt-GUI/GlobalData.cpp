#include "GlobalData.h"

///data
QString GlobalData::g_myKeyStr;
QString GlobalData::g_myNameStr;
QString GlobalData::g_avatarPathStr;
QFont GlobalData::g_font;



///net
QString GlobalData::g_localHostIP;

QString GlobalData::g_currentTime()
{
  return QDateTime::currentDateTime().toString("yyyy_MM_dd_hh_mm_ss");
}




////////Data Standard:////////
/*
usrInfoStrList:
usrKey<<usrName<<ipAddr<<avatarPath
l
myProfile:
usrKey<<usrName<<avatarPath


*/
