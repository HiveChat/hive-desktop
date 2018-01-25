#include "SettingsTab.h"

SettingsTab::SettingsTab(QWidget *parent) : QWidget(parent)
{
  messaging_btn = new MenuButton("messaging", GUI::StaticStackType::Settings_Messaging, this);
  messaging_btn->setDefaultPixmap(":/img/img/messaging_0.png");
  messaging_btn->setHoveredPixmap(":/img/img/messaging_1.png");

  profile_btn = new MenuButton("profile", GUI::StaticStackType::Settings_Profile, this);
  profile_btn->setDefaultPixmap(":/img/img/profile_0.png");
  profile_btn->setHoveredPixmap(":/img/img/profile_1.png");

  style_btn = new MenuButton("style", GUI::StaticStackType::Settings_Style, this);
  style_btn->setDefaultPixmap(":/img/img/style_0.png");
  style_btn->setHoveredPixmap(":/img/img/style_1.png");

  questions_btn = new MenuButton("questions", GUI::StaticStackType::Settings_Questions, this);
  questions_btn->setDefaultPixmap(":/img/img/question_0.png");
  questions_btn->setHoveredPixmap(":/img/img/question_1.png");

  update_btn = new MenuButton("update", GUI::StaticStackType::Settings_Update, this);
  update_btn->setDefaultPixmap(":/img/img/update_0.png");
  update_btn->setHoveredPixmap(":/img/img/update_1.png");

  ////main layout
  main_layout = new QVBoxLayout(this);
  main_layout->setContentsMargins(30,20,20,0);
  main_layout->setSpacing(20);
  main_layout->setAlignment(Qt::AlignTop);
  main_layout->addWidget(messaging_btn);
  main_layout->addWidget(profile_btn);
  main_layout->addWidget(style_btn);
  main_layout->addWidget(update_btn);
  main_layout->addWidget(questions_btn);

  ///for test period
  style_btn->setHidden(true);


  this->setParent(parent);

}

SettingsTab::~SettingsTab()
{

}


