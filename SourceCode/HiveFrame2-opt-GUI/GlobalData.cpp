#include "GlobalData.h"
#include <QPalette>
///UI
QFont GlobalData::g_font;
QColor GlobalData::g_windowColor = QColor(255,255,255);
QColor GlobalData::g_alphaTabColor = QColor(255,255,255,240);
QColor GlobalData::g_tabColor = QColor(0,0,0,0);

QColor GlobalData::g_chatBubbleColorI = QColor(255,215,126);
QColor GlobalData::g_chatBubbleColorO = QColor(225,225,225);

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
