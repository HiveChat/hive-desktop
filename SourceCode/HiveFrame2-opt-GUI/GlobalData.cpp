#include "GlobalData.h"

///UI
QFont GlobalData::g_font;
QColor GlobalData::g_windowColor = QColor(255,255,255);
QColor GlobalData::g_alphaTabColor = QColor(0,0,0,15);
QColor GlobalData::g_tabColor = QColor(240,240,240);


///data
QString GlobalData::g_myKeyStr;
QString GlobalData::g_myNameStr;
QString GlobalData::g_avatarPathStr;

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
