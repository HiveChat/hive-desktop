#include "SettingsStack_profile.h"

GuiSettingsStack_profile::GuiSettingsStack_profile(QWidget *parent)
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
  avatar_btn = new GuiAvatarButton(GlobalData::settings_struct.profile_avatar_str, 100, this);
  QButtonGroup *avatar_option_group = new QButtonGroup(this);
  QVBoxLayout *avatar_option_layout = new QVBoxLayout();
  avatar_option_layout->addWidget(avatar_btn);

  QString current_avatar_name = avatar_hash.key(GlobalData::settings_struct.profile_avatar_str);

  foreach(QString temp_avatar_name_str, avatar_hash.keys())
    {
      QRadioButton *temp_radio_btn = new QRadioButton(temp_avatar_name_str, this);
      temp_radio_btn->setChecked(temp_avatar_name_str == current_avatar_name);
      avatar_option_group->addButton(temp_radio_btn);
      avatar_option_layout->addWidget(temp_radio_btn);
      avatar_radio_btn_list.append(temp_radio_btn);
    }

  addItem("\tAvatar:", avatar_option_layout);

  //usrname
  QLineEdit *usr_name_line_edit = new QLineEdit(GlobalData::settings_struct.profile_name_str,this);
  usr_name_line_edit->setMaximumWidth(200);
  addItem("\tUser Name:", usr_name_line_edit);

  //usrkey
  QLineEdit *usr_key_line_edit = new QLineEdit(GlobalData::settings_struct.profile_name_str,this);
  usr_key_line_edit->setText(GlobalData::settings_struct.profile_key_str);
  usr_key_line_edit->setCursor(QCursor(Qt::IBeamCursor));
  usr_key_line_edit->setReadOnly(true);
  usr_key_line_edit->setMaximumWidth(200);
  addItem("\tUser Key:", usr_key_line_edit);


  connect(avatar_option_group, SIGNAL(buttonClicked(QAbstractButton*)),
          this, SLOT(onRadioClicked(QAbstractButton*)));
  connect(usr_name_line_edit, &QLineEdit::textEdited,
          this, &GuiSettingsStack_profile::onUsrNameChanged);

  this->setParent(parent);
}

GuiSettingsStack_profile::~GuiSettingsStack_profile()
{
  foreach (QRadioButton *object, avatar_radio_btn_list)
    {
      object->deleteLater();
    }
}

void GuiSettingsStack_profile::onRadioClicked(QAbstractButton *abstractButton)
{
  GlobalData::settings_struct.profile_avatar_str = avatar_hash.value(abstractButton->text());
  avatar_btn->setAvatar(GlobalData::settings_struct.profile_avatar_str);
  GlobalData::settings_struct.modified_lock = true;
}

void GuiSettingsStack_profile::onUsrNameChanged(QString usr_name)
{
  GlobalData::settings_struct.profile_name_str = usr_name;
  GlobalData::settings_struct.modified_lock = true;
}

