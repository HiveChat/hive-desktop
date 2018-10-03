#include "SettingsStack_messaging.h"

SettingsStack_messaging::SettingsStack_messaging(QWidget *parent)
{
  this->setUpUI(LayoutStyle::Linear);

  setIcon(":/img/img/messaging.png");
  setTitle("Settings");
  setSubTitle("messaging");

  addTag("Text Bubble");
  in_bubble_picker = new ColorPicker(&Global::settings.chat_bubble_color_i, this);
  addItem("\tReceived message bubble colour:", in_bubble_picker);
  out_bubble_picker = new ColorPicker(&Global::settings.chat_bubble_color_o, this);
  addItem("\tSent message bubble colour:       ", out_bubble_picker);
  QPushButton *push_btn = new QPushButton("reset", this);
  push_btn->setMaximumWidth(70);
  connect(push_btn, &QPushButton::clicked,
          [this](){
            Global::settings.chat_bubble_color_i = Global::color_defaultChatBubbleI;
            Global::settings.chat_bubble_color_o = Global::color_defaultChatBubbleO;
            Global::settings.modified = true;
            in_bubble_picker->repaint();
            out_bubble_picker->repaint();
          });
  addItem("\tDefault color scheme:      ", push_btn);


  addTag("Notifications");
  QCheckBox *enable_notify_box = new QCheckBox(this);
  enable_notify_box->setChecked(Global::settings.notification.message_notification);
  connect(enable_notify_box, &QCheckBox::toggled,
          [this](bool toggled){
            Global::settings.notification.message_notification = toggled;
            Global::settings.modified = true;
          });
#ifndef Q_OS_WIN
  addItem("\tEnable notifications\t\t\t          ", enable_notify_box);
#else
  addItem("\tEnable notifications\t\t\t\t", enable_notify_box);
#endif
  QCheckBox *show_detail_box = new QCheckBox(this);
  show_detail_box->setChecked(Global::settings.notification.message_detail_notification);
  connect(show_detail_box, &QCheckBox::toggled,
          [this](bool toggled){
            Global::settings.notification.message_detail_notification = toggled;
            Global::settings.modified = true;
          });
#ifndef Q_OS_WIN
  addItem("\tShow message detail\t\t          ", show_detail_box);
#else
  addItem("\tShow message detail\t\t\t\t", show_detail_box);
#endif
  addTag("History Cleaner");
  clear_btn = new QPushButton("clear", this);
  clear_btn->setMaximumWidth(70);
  connect(clear_btn, &QPushButton::clicked,
          [this](){
            if(make_sure == 0)
              {
                clear_btn->setText("sure?");
                make_sure ++;
              }
            else if(make_sure == 1)
              {
                clear_btn->setText("go!");
                make_sure ++;
              }
            if(make_sure == 2)
              {
#ifndef Q_OS_WIN
                const QString appDataLocalPath = QStandardPaths::writableLocation(QStandardPaths::DataLocation);
#else
                const QString appDataLocalPath = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
#endif
                QDir dir(QString(appDataLocalPath + "/usr/"));
                if(dir.removeRecursively())
                  {
                    clear_btn->setText("cleared");
                    clear_btn->setDisabled(true);
                  }
                else
                  {
                    clear_btn->setText("failed");
                  }
              }
          });
  addItem("\tDelete ALL Message History:      ", clear_btn);



  this->setParent(parent);
}

SettingsStack_messaging::~SettingsStack_messaging()
{

}

