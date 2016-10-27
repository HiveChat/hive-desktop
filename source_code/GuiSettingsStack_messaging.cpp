#include "GuiSettingsStack_messaging.h"

GuiSettingsStack_messaging::GuiSettingsStack_messaging(QWidget *parent)
{
  this->setUpUI(LayoutStyle::Linear);

  setIcon(":/img/img/messaging.png");
  setTitle("Settings");
  setSubTitle("messaging");

  addTag("Text Bubble");
  in_bubble_picker = new GuiColorPicker(&GlobalData::settings_struct.chat_bubble_color_i, this);
  addItem("\tReceived message bubble colour:", in_bubble_picker);
  out_bubble_picker = new GuiColorPicker(&GlobalData::settings_struct.chat_bubble_color_o, this);
  addItem("\tSent message bubble colour:       ", out_bubble_picker);
  QPushButton *push_btn = new QPushButton("reset", this);
  push_btn->setMaximumWidth(70);
  connect(push_btn, &QPushButton::clicked,
          [this](){
            GlobalData::settings_struct.chat_bubble_color_i = GlobalData::color_defaultChatBubbleI;
            GlobalData::settings_struct.chat_bubble_color_o = GlobalData::color_defaultChatBubbleO;
            GlobalData::settings_struct.modified_lock = true;
            in_bubble_picker->repaint();
            out_bubble_picker->repaint();
          });
  addItem("\tDefault color scheme:      ", push_btn);

  addTag("Notifications");
  QCheckBox *enable_notify_box = new QCheckBox(this);
  connect(enable_notify_box, &QCheckBox::toggled,
          [this](bool toggled){
            GlobalData::settings_struct.notification.enabled = toggled;
            GlobalData::settings_struct.modified_lock = true;
          });
  addItem("\tEnable notifications\t\t\t          ", enable_notify_box);
  QCheckBox *show_detail_box = new QCheckBox(this);
  connect(show_detail_box, &QCheckBox::toggled,
          [this](bool toggled){
            GlobalData::settings_struct.notification.show_detail = toggled;
            GlobalData::settings_struct.modified_lock = true;
          });
  addItem("\tShow message detail\t\t          ", show_detail_box);

  this->setParent(parent);
}

GuiSettingsStack_messaging::~GuiSettingsStack_messaging()
{

}

