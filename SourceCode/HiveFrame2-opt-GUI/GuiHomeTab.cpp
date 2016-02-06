#include "GuiHomeTab.h"
#include <stdlib.h>

GuiHomeTab::GuiHomeTab(QWidget *parent) : QWidget(parent)
{
  QFont label_font("Futura");
  //label_font.setPointSize(20);
  label_font.setPointSize(20);

  welcome_label = new GuiTextButton("welcome");
  issues_label = new GuiTextButton("issues");
  files_label = new GuiTextButton("files");
  settings_label = new GuiTextButton("settings");

  welcome_label->setFont(label_font);
  welcome_label->setAlignment(Qt::AlignHCenter);
  issues_label->setFont(label_font);
  issues_label->setAlignment(Qt::AlignHCenter);
  files_label->setFont(label_font);
  files_label->setAlignment(Qt::AlignHCenter);
  settings_label->setFont(label_font);
  settings_label->setAlignment(Qt::AlignHCenter);

  ////main layout
  main_layout = new QVBoxLayout(this);
  main_layout->setContentsMargins(10,20,10,10);
  main_layout->setSpacing(20);
  main_layout->setAlignment(Qt::AlignTop);
  main_layout->addWidget(welcome_label);
  main_layout->addWidget(issues_label);
  main_layout->addWidget(files_label);
  main_layout->addWidget(settings_label);

  this->setParent(parent);

}

GuiHomeTab::~GuiHomeTab()
{

}

