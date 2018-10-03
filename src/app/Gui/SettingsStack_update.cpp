#include "SettingsStack_update.h"

SettingsStack_update::SettingsStack_update(QWidget *parent)
{
  this->setUpUI(LayoutStyle::Linear);

  setIcon(":/img/img/update.png");
  setTitle("Settings");
  setSubTitle("update");

  addTag("Check update");
  QCheckBox *auto_check_box = new QCheckBox(this);
  auto_check_box->setChecked(Global::settings.update.auto_check_update);
  connect(auto_check_box, &QCheckBox::toggled,
          [this](bool toggled){
            Global::settings.update.auto_check_update = toggled;
            Global::settings.modified = true;
          });
  addItem("\tAuto check update:\t\t\t          ", auto_check_box);

  QCheckBox *show_notification_box = new QCheckBox(this);
  show_notification_box->setChecked(Global::settings.notification.update_notification);
  connect(show_notification_box, &QCheckBox::toggled,
          [this](bool toggled){
            Global::settings.notification.update_notification = toggled;
            Global::settings.modified = true;
          });
  addItem("\tShow update notification:\t\t          ", show_notification_box);


  addTag("Hive version: ");
  addItem("Current version: ",
          QString("%1.%2.%3")
          .arg(Global::current_version[0])
          .arg(Global::current_version[1])
          .arg(Global::current_version[2]));
  addItem("Current features:"
          , "1. Added notifications for messaging\n"
            "2. Added notifications for updates\n"
            "3. Added update helper\n"
            "4. Added badge number for unread message count\n"
            "5. Added more settings\n"
            "6. Updated Icon\n"
            "7. Optimized typeface on Windows\n"
            "8. Optimized chat area switch algorithm to reduce RAM\n"
            "9. Fixed unexpected quit caused by unrecognized user\n"
          , false);

  bool updateLoaded = (Global::update_struct.version[0] != 0
                       || Global::update_struct.version[1] != 0
                       || Global::update_struct.version[2] != 0);

  bool updateAvailable = memcmp(Global::update_struct.version,
                           Global::current_version,
                           sizeof(Global::current_version))  != 0;

  if(updateLoaded && updateAvailable)
    {
      QLabel *label = new QLabel("<a href=\"http://hivechat.org\">https://hivechat.org/downloads.html</a>", this);
      label->setOpenExternalLinks(true);

      addTag("Available Update:");
      addItem("\tGo to update!\t\t             ", label);
      addItem("New version: version:\t", Global::update_struct.title, false);
      addItem("Update version: version:\t",
              QString("%1.%2.%3")
              .arg(Global::update_struct.version[0])
              .arg(Global::update_struct.version[1])
              .arg(Global::update_struct.version[2]),
              false);
      addItem("Features and Fixes: \t", Global::update_struct.message);
    }


  this->setParent(parent);
}
