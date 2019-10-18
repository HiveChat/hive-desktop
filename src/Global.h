#ifndef GLOBALDATA_H
#define GLOBALDATA_H


#include "UsrData.h"
#include "GlobalType.h"
#include "Log.h"
#include "Bee.h"

#include <QDate>
#include <QFont>
#include <QHash>
#include <QPalette>
#include <QColor>
#include <QStandardPaths>
#include <QDebug>
#include <QUrl>

#define BROADCAST_UUID "{00000000-0000-0000-0000-000000000000}"



class Global
{
public:
  ///UI

  static int window_dpr;
  static int window_defaultWidth;
  static int window_defaultHeight;

  static QFont font_main;
  static QFont font_chatTextEditor;
  static QFont font_chatBubble;
  static QFont font_contactWidgetUsrName;
  static QFont font_contactWidgetIpAddr;
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
  static QColor color_contact_selection;

  static QColor color_defaultChatBubbleI;
  static QColor color_defaultChatBubbleO;
  static QColor color_mChatBubbleI;
  static QColor color_mChatBubbleO;

  static QPalette palette_bkg_normalWhite;
  static QPalette palette_bkg_transparent;
  static QPalette palette_txt_brown;

  ///data
  static int current_version[3];
  static Settings::SettingsStruct settings;
  static UpdateStruct update_struct;
  static QUrl update_url;
  static QUrl download_url;

  static QMultiHash<QString, QPair<int, int> > file_tran_progress_hash;
                  //key           total done
  static QList<QJsonObject> message_queue;

  static const std::string data_location_dir;
  static const std::string user_data_dir;
  static const std::string log_dir;

  static const std::string contacts_file_dir;
  static const std::string settings_file_dir;
  static const std::string update_file_dir;


  ///net
  static QString g_localHostIP; //<< Deprecated! DELETE!
  ///other
  static QString getCurrentTime();
  static QString getRandomString(const int &digit);


  static bool versionCompare(const int (&fresh)[3], const int (&old)[3]);

  ///debug
  static void TEST_printUsrProfile(const UsrProfile &p, const QString &str);

};




#endif // GLOBALDATA_H
