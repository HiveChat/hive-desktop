#ifndef APPDATA_H
#define APPDATA_H


#include <QFont>
#include <QColor>

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
  static bool set_window_width;
  static bool set_window_height;
  static bool set_profile_avatar;
  static bool set_profile_name;
  static bool set_profile_id;



};

#endif // APPDATA_H




