#include "GlobalData.h"

///data
QString GlobalData::g_myKeyStr;
QString GlobalData::g_myNameStr;
QString GlobalData::g_avatarPathStr;
QFont GlobalData::g_font;
QColor GlobalData::g_windowColor = QColor(250,250,250);


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
