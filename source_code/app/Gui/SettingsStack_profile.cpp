#include "SettingsStack_profile.h"

SettingsStack_profile::SettingsStack_profile(QWidget *parent)
{
  this->setUpUI(LayoutStyle::Linear);

  avatar_hash.insert("Flying Bee", ":/avatar/avatar/bee.png");
  avatar_hash.insert("Hive", ":/img/img/icon.png");
  avatar_hash.insert("Fat Bee", ":/avatar/avatar/fat.png");
  avatar_hash.insert("Lady Bug", ":/avatar/avatar/ladybug.png");
  avatar_hash.insert("Disk", ":/avatar/avatar/disk.png");
  avatar_hash.insert("Sunflower", ":/avatar/avatar/sunflower.png");
  avatar_hash.insert("Worm", ":/avatar/avatar/worm.png");
  avatar_hash.insert("Default", ":/avatar/avatar/default.png");
  avatar_hash.insert("Spider", ":/avatar/avatar/spider.png");

  setIcon(":/img/img/profile.png");
  setTitle("Settings");
  setSubTitle("profile");
  addTag("User information");

  //avatar
  QButtonGroup *avatar_option_group = new QButtonGroup(this);
  QVBoxLayout *avatar_option_layout = new QVBoxLayout();

  QString current_avatar_name = avatar_hash.key(Global::settings.profile_avatar_str);

  foreach(QString temp_avatar_name_str, avatar_hash.keys())
    {
      QRadioButton *temp_radio_btn = new QRadioButton(temp_avatar_name_str, this);
      temp_radio_btn->setChecked(temp_avatar_name_str == current_avatar_name);
      avatar_option_group->addButton(temp_radio_btn);
      avatar_option_layout->addWidget(temp_radio_btn);
      avatar_radio_btn_list.append(temp_radio_btn);
    }

  avatar_composer = new AvatarComposer(QSize(200,200),this);
  avatar_composer->setSourceImage(Global::settings.profile_avatar_str);
  addItem("\tAvatar Editor:", avatar_composer);
  addItem("\tAvatar:", avatar_option_layout);

  //usrname
  QLineEdit *usr_name_line_edit = new QLineEdit(Global::settings.profile_name_str,this);
  usr_name_line_edit->setMaximumWidth(200);
  addItem("\tUser Name:", usr_name_line_edit);

  //usrkey
  QLineEdit *usr_key_line_edit = new QLineEdit(Global::settings.profile_name_str,this);
  usr_key_line_edit->setText(Global::settings.profile_key_str);
  usr_key_line_edit->setCursor(QCursor(Qt::IBeamCursor));
  usr_key_line_edit->setReadOnly(true);
  usr_key_line_edit->setMaximumWidth(200);
  addItem("\tUser Key:", usr_key_line_edit);


  connect(avatar_option_group, SIGNAL(buttonClicked(QAbstractButton*)),
          this, SLOT(onRadioClicked(QAbstractButton*)));
  connect(usr_name_line_edit, &QLineEdit::textEdited,
          this, &SettingsStack_profile::onUsrNameChanged);

  this->setParent(parent);
}

SettingsStack_profile::~SettingsStack_profile()
{
  foreach (QRadioButton *object, avatar_radio_btn_list)
    {
      object->deleteLater();
    }
}

void SettingsStack_profile::onRadioClicked(QAbstractButton *abstractButton)
{
  Global::settings.profile_avatar_str = avatar_hash.value(abstractButton->text());
  avatar_composer->setSourceImage(Global::settings.profile_avatar_str);
  Global::settings.modified = true;
}

void SettingsStack_profile::onUsrNameChanged(QString usr_name)
{
  Global::settings.profile_name_str = usr_name;
  Global::settings.modified = true;
}

