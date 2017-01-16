#ifndef GLOBALDATA_H
#define GLOBALDATA_H


#include "UsrData.h"
#include "GlobalType.h"

#include <QDate>
#include <QFont>
#include <QHash>
#include <QPalette>
#include <QColor>
#include <QStandardPaths>
#include <QDebug>



class GlobalData
{
public:
  ///UI

  static int window_defaultWidth;
  static int window_defaultHeight;

  static QFont font_main;
  static QFont font_chatTextEditor;
  static QFont font_chatBubble;
  static QFont font_combWidgetUsrName;
  static QFont font_combWidgetIpAddr;
  static QFont font_menuButton;
  static QFont font_scrollStackTitle;
  static QFont font_scrollStackSubtitle;

  //!base color
  static QColor color_darkGrey;
  static QColor color_lightGrey;
  static QColor color_brown;
  static QColor color_hiveYellow;
  static QColor color_lightYellow;

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
  static int current_version[3];
  static Settings::SettingsStruct settings_struct;
  static UpdateStruct update_struct;
  static QUrl update_url;
  static QUrl download_url;

  static QHash<QString, UsrProfileStruct> saved_usr_profile_hash;
  static QHash<QString, UsrData*> online_usr_data_hash;//used

  ///net
  static QString g_localHostIP;
  ///other
  static QString getCurrentTime();
  static QString getRandomString(const int &digit);


  static bool versionCompare(const int (&old)[3], const int (&fresh)[3]);

  ///debug
  static void TEST_printUsrProfileStruct(const UsrProfileStruct &usrProfileStruct, const QString &str);

};




#endif // GLOBALDATA_H
