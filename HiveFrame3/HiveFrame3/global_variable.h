#ifndef APPDATA_H
#define APPDATA_H

#include <QFont>

#define GUI_COLOR_DARK_GREY QColor(100,100,100)
#define GUI_COLOR_LIGHT_GREY QColor(225,225,225)
#define GUI_COLOR_BROWN QColor(103,72,0)
#define GUI_COLOR_HIVE_YELLOW QColor(255,181,0)
#define GUI_COLOR_LIGHT_YELLOW QColor(255,215,126)

class GlobalVar
{
public:
  static QFont gui_font_chatBubble;
  static QFont gui_font_chatEditor;
  static QFont gui_font_combWidgetTitle;
  static QFont gui_font_combWidgetSubtitle;
  static QFont gui_font_menuButton;
  static QFont gui_font_scrollStackTitle;
  static QFont gui_font_scrollStackSubtitle;
  static QFont gui_font_scrollStackContent;
  static QColor gui_color_bkg_window;
  static QColor gui_color_bkg_tabBlock;
  static QColor gui_color_bkg_combScrollArea;
  static QColor gui_color_bkg_chatBubbleIn;
  static QColor gui_color_bkg_chatBubbleOut;

  static bool set_notify_update;
  static bool set_notify_message;
  static bool set_notify_message_content;
  static bool set_update_check;
  static bool set_update_auto;

};

#endif // APPDATA_H



struct SettingsStruct
{
  bool modified_lock;

  int window_width;
  int window_height;

  QColor chat_bubble_color_i;
  QColor chat_bubble_color_o;

  QString profile_avatar_str;
  QString profile_name_str;
  QString profile_key_str;

  Notification notification;
  Update update;
};
