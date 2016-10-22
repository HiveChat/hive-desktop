#ifndef GLOBALDATA_H
#define GLOBALDATA_H


#include "UsrData.h"
#include "GlobalType.h"

#include <QDate>
#include <QFont>
#include <QMap>
#include <QPalette>
#include <QColor>
#include <QStandardPaths>
#include <QDebug>



class GlobalData
{
public:
  ///UI
  static QFont font_main;
  static QFont font_chatTextEditor;
  static QFont font_chatBubble;
  static QFont font_combWidgetUsrName;
  static QFont font_combWidgetIpAddr;
  static QFont font_menuButton;
  static QFont font_scrollStackTitle;
  static QFont font_scrollStackSubtitle;

  //!base color
  static QColor bc_darkGrey;
  static QColor bc_lightGrey;
  static QColor bc_brown;
  static QColor bc_hiveYellow;
  static QColor bc_lightYellow;

  static QColor color_window;
  static QColor color_alphaTab;
  static QColor color_tab;

  static QColor color_defaultChatBubbleI;
  static QColor color_defaultChatBubbleO;
  static QColor color_mChatBubbleI;
  static QColor color_mChatBubbleO;

  static QPalette palette_bkg_normalWhite;
  static QPalette palette_bkg_transparent;
  static QPalette palette_txt_brown;

  ///data
  static char g_version[3];
  static Settings::SettingStruct g_settings_struct;
  static QMap<QString, UsrProfileStruct> saved_usr_profile_map;
  static QMap<QString, UsrProfileStruct> online_usr_profile_map;

  static QMap<QString, UsrData*> online_usr_data_map;//used


  ///net
  static QString g_localHostIP;

  ///other
  static QString g_currentTime();
  static QString getRandomString(const int &digit);

  ///debug
  static void TEST_printUsrProfileStruct(const UsrProfileStruct &usrProfileStruct, const QString &str);

};




#endif // GLOBALDATA_H
