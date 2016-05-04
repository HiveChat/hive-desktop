#include "GuiSettingsStack_messaging.h"

GuiSettingsStack_messaging::GuiSettingsStack_messaging(QWidget *parent)
{
  setIcon(":/img/img/messaging.png");
  setTitle("Settings");
  setSubTitle("messaging");
  setTag("Text Bubble");

  GuiColorPicker *in_bubble_picker = new GuiColorPicker(&GlobalData::g_settings_struct.chat_bubble_color_i, this);
  addItem("\tReceived message bubble colour:", in_bubble_picker);

  GuiColorPicker *out_bubble_picker = new GuiColorPicker(&GlobalData::g_settings_struct.chat_bubble_color_o, this);
  addItem("\tSent message bubble colour:       ", out_bubble_picker);

  this->setParent(parent);
}

GuiSettingsStack_messaging::~GuiSettingsStack_messaging()
{

}

