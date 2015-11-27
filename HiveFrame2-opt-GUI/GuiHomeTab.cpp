#include "GuiHomeTab.h"
#include <stdlib.h>

GuiHomeTab::GuiHomeTab(QWidget *parent) : QWidget(parent)
{
  welcome_label = new GuiTextButton(" welcome page");
  issues_label = new GuiTextButton(" issues");
  files_label = new GuiTextButton(" files received");
  settings_label = new GuiTextButton(" settings");

  ////main layout
  main_layout = new QVBoxLayout(this);
  main_layout->setContentsMargins(10,20,10,10);
  main_layout->setSpacing(20);
  main_layout->setAlignment(Qt::AlignTop);
  main_layout->addWidget(welcome_label);
  main_layout->addWidget(issues_label);
  main_layout->addWidget(files_label);
  main_layout->addWidget(settings_label);


}

GuiHomeTab::~GuiHomeTab()
{

}

