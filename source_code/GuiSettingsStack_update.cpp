#include "GuiSettingsStack_update.h"

GuiSettingsStack_update::GuiSettingsStack_update(QWidget *parent)
{
  this->setUpUI(LayoutStyle::Linear);

  setIcon(":/img/img/update.png");
  setTitle("Settings");
  setSubTitle("update");

  addTag("Check update");
  QCheckBox *auto_check_box = new QCheckBox(this);
  auto_check_box->setChecked(GlobalData::settings_struct.update.auto_check_update);
  connect(auto_check_box, &QCheckBox::toggled,
          [this](bool toggled){
            GlobalData::settings_struct.update.auto_check_update = toggled;
            GlobalData::settings_struct.modified_lock = true;
          });
  addItem("\tAuto check update\t\t\t          ", auto_check_box);

  QCheckBox *show_notification_box = new QCheckBox(this);
  show_notification_box->setChecked(GlobalData::settings_struct.notification.update_notification);
  connect(show_notification_box, &QCheckBox::toggled,
          [this](bool toggled){
            GlobalData::settings_struct.notification.update_notification = toggled;
            GlobalData::settings_struct.modified_lock = true;
          });
  addItem("\tShow notifications\t\t\t          ", show_notification_box);

  this->setParent(parent);
}
