#include "GuiHomeTab.h"
#include <stdlib.h>

GuiHomeTab::GuiHomeTab(QWidget *parent) : QWidget(parent)
{
  QFont label_font("Futura");
  //label_font.setPointSize(20);
  label_font.setPointSize(20);

  welcome_btn = new GuiLabelButton(this);
  issues_btn = new GuiLabelButton(this);
  //files_btn = new GuiLabelButton(this);
  //settings_btn = new GuiLabelButton(this);

  welcome_btn->setDefaultPixmap("/Users/Echo/Desktop/welcome_0.png");
  welcome_btn->setHoveredPixmap("/Users/Echo/Desktop/welcome_1.png");

  issues_btn->setDefaultPixmap("/Users/Echo/Desktop/settings_0.png");
  issues_btn->setHoveredPixmap("/Users/Echo/Desktop/settings_1.png");

  welcome_label = new GuiTextButton("welcome");
  issues_label = new GuiTextButton("issues");
  files_label = new GuiTextButton("files");
  settings_label = new GuiTextButton("settings");

  welcome_label->setFont(label_font);
  welcome_label->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
  issues_label->setFont(label_font);
  issues_label->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
  files_label->setFont(label_font);
  files_label->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
  settings_label->setFont(label_font);
  settings_label->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

  ////main layout
  main_layout = new QGridLayout(this);
  main_layout->setContentsMargins(30,20,50,10);
  main_layout->setHorizontalSpacing(0);
  main_layout->setAlignment(Qt::AlignTop);
  main_layout->addWidget(welcome_btn,0,0);
  main_layout->addWidget(issues_btn,1,0);
  main_layout->addWidget(welcome_label,0,1);
  main_layout->addWidget(issues_label,1,1);
  main_layout->addWidget(files_label,2,1);
  main_layout->addWidget(settings_label,3,1);

  this->setParent(parent);

}

GuiHomeTab::~GuiHomeTab()
{

}

