#include "GuiHomeTab.h"
#include <stdlib.h>

GuiHomeTab::GuiHomeTab(QWidget *parent) : QWidget(parent)
{
  QFont label_font("Futura");
  //label_font.setPointSize(20);
  label_font.setPointSize(20);

  welcome_btn = new GuiMenuButton("welcome", this);
  settings_btn = new GuiMenuButton("settings", this);

  welcome_btn->setDefaultPixmap("/Users/Echo/Desktop/welcome_0.png");
  welcome_btn->setHoveredPixmap("/Users/Echo/Desktop/welcome_1.png");

  settings_btn->setDefaultPixmap("/Users/Echo/Desktop/settings_0.png");
  settings_btn->setHoveredPixmap("/Users/Echo/Desktop/settings_1.png");

  ////main layout
  main_layout = new QVBoxLayout(this);
  main_layout->setContentsMargins(30,20,20,0);
  main_layout->setSpacing(20);
  main_layout->setAlignment(Qt::AlignTop);
  main_layout->addWidget(welcome_btn);
  main_layout->addWidget(settings_btn);


  this->setParent(parent);

}

GuiHomeTab::~GuiHomeTab()
{

}

