#include "GuiSettingsStack_profile.h"

GuiSettingsStack_profile::GuiSettingsStack_profile(QWidget *parent)
{
  avatar_map.insert("Bee", ":/img/img/icon.png");
  avatar_map.insert("Fat Bee", ":/avatar/avatar/bee.png");
  avatar_map.insert("Lady Bug", ":/avatar/avatar/ladybug.png");
  avatar_map.insert("Disk", ":/avatar/avatar/disk.png");
  avatar_map.insert("Sunflower", ":/avatar/avatar/sunflower.png");
  avatar_map.insert("Worm", ":/avatar/avatar/worm.png");
  avatar_map.insert("Default", ":/avatar/avatar/default.png");

  setIcon(":/img/img/profile_0.png");
  setTitle("Settings");
  setSubTitle("profile");

  QLabel *usr_info_label = new QLabel("User information", this);
  QFont font("Futura");//Verdana
  font.setPointSize(15);
  usr_info_label->setFont(font);
  usr_info_label->setPalette(text_palette);

  QFrame *top_line = new QFrame(this);
  top_line->setFrameShape(QFrame::HLine);
  top_line->setFrameShadow(QFrame::Plain);
  top_line->setFixedHeight(1);
  top_line->setFixedWidth(580);
  top_line->setStyleSheet ("QFrame{  background: #CFCFCF; border: 0px transparent;  }");


  QLabel *avatar_label = new QLabel("\tAvatar:", this);
  avatar_label->setAlignment(Qt::AlignTop);
  QFont sub_font("Futura");//Verdana
  avatar_label->setFont(sub_font);
  avatar_label->setPalette(sub_text_palette);

  avatar_btn = new GuiAvatarButton(GlobalData::g_avatarPathStr, 100, this);

  QButtonGroup *avatar_option_group = new QButtonGroup(this);

  QVBoxLayout *avatar_option_layout = new QVBoxLayout();
  avatar_option_layout->addWidget(avatar_btn);

  foreach(QString temp_avatar_name_str, avatar_map.keys())
    {
      QRadioButton *temp_radio_btn = new QRadioButton(temp_avatar_name_str, this);
      avatar_option_group->addButton(temp_radio_btn);
      avatar_option_layout->addWidget(temp_radio_btn);
      avatar_radio_btn_list.append(temp_radio_btn);
    }


  QHBoxLayout *avatar_layout = new QHBoxLayout();
//  avatar_layout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
  avatar_layout->setContentsMargins(0,30,200,0);
  avatar_layout->setSpacing(30);
  avatar_layout->addWidget(avatar_label);
  avatar_layout->addLayout(avatar_option_layout);

  //usrname
  QLabel *usr_name_label = new QLabel("\tUser Name:", this);
  usr_name_label->setFont(sub_font);
  usr_name_label->setPalette(sub_text_palette);

  QLineEdit *usr_name_line_edit = new QLineEdit(GlobalData::g_myNameStr,this);
  usr_name_line_edit->setMaximumWidth(200);

  QHBoxLayout *usr_name_layout = new QHBoxLayout();
//  usr_name_layout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
  usr_name_layout->setContentsMargins(0,10,200,0);
  usr_name_layout->setSpacing(30);
  usr_name_layout->addWidget(usr_name_label);
  usr_name_layout->addWidget(usr_name_line_edit);

  //usrkey
  QLabel *usr_key_label = new QLabel("\tUser Key:", this);
  usr_key_label->setFont(sub_font);
  usr_key_label->setPalette(sub_text_palette);

  QLineEdit *usr_key_line_edit = new QLineEdit(GlobalData::g_myNameStr,this);
  usr_key_line_edit->setText(GlobalData::g_myKeyStr);
  usr_key_line_edit->setCursor(QCursor(Qt::IBeamCursor));
  usr_key_line_edit->setReadOnly(true);
  usr_key_line_edit->setMaximumWidth(200);

  QHBoxLayout *usr_key_layout = new QHBoxLayout();
//  usr_name_layout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
  usr_key_layout->setContentsMargins(0,10,200,0);
  usr_key_layout->setSpacing(30);
  usr_key_layout->addWidget(usr_key_label);
  usr_key_layout->addWidget(usr_key_line_edit);

  central_layout->setAlignment(Qt::AlignCenter);
  central_layout->setContentsMargins(30,30,0,50);
  central_layout->addWidget(usr_info_label);
  central_layout->addWidget(top_line);
  central_layout->addLayout(avatar_layout);
  central_layout->addLayout(usr_name_layout);
  central_layout->addLayout(usr_key_layout);
//  central_layout->addSpacing(15);

  connect(avatar_option_group, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(onRadioClicked(QAbstractButton*)));
  connect(usr_name_line_edit, SIGNAL(textEdited(QString)), this, SLOT(onUsrNameChanged(QString)));

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
  GlobalData::g_avatarPathStr = avatar_map.value(abstractButton->text());
  avatar_btn->setAvatar(GlobalData::g_avatarPathStr);
}

void GuiSettingsStack_profile::onUsrNameChanged(QString usr_name)
{
  GlobalData::g_myNameStr = usr_name;
}

