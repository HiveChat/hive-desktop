#include "global_variable.h"

QFont GlobalVar::gui_font_chatBubble;
QFont GlobalVar::gui_font_chatEditor;
QFont GlobalVar::gui_font_combWidgetTitle;
QFont GlobalVar::gui_font_combWidgetSubtitle;
QFont GlobalVar::gui_font_menuButton;
QFont GlobalVar::gui_font_scrollStackTitle;
QFont GlobalVar::gui_font_scrollStackSubtitle;
QFont GlobalVar::gui_font_scrollStackContent;
QColor GlobalVar::gui_color_bkg_window = Qt::white;
QColor GlobalVar::gui_color_bkg_tabBlock = QColor(255,255,255,230);
QColor GlobalVar::gui_color_bkg_combScrollArea = Qt::transparent;
QColor GlobalVar::gui_color_bkg_chatBubbleIn = GUI_COLOR_LIGHT_YELLOW;
QColor GlobalVar::gui_color_bkg_chatBubbleOut = GUI_COLOR_LIGHT_GREY;

bool GlobalVar::set_notify_update;
bool GlobalVar::set_notify_message;
bool GlobalVar::set_notify_message_content;
bool GlobalVar::set_update_check;
bool GlobalVar::set_update_auto;


