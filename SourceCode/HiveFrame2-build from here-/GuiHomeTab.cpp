#include "GuiHomeTab.h"
#include <stdlib.h>

GuiHomeTab::GuiHomeTab(QWidget *parent) : QWidget(parent)
{
  QFont label_font("Futura");
  //label_font.setPointSize(20);
  label_font.setPointSize(20);

  welcome_btn = new GuiMenuButton("welcome", Home_Welcome, this);
  storage_btn = new GuiMenuButton("file storage", Home_Storage, this);

  welcome_btn->setDefaultPixmap(":/img/img/welcome_0.png");
  welcome_btn->setHoveredPixmap(":/img/img/welcome_1.png");

  storage_btn->setDefaultPixmap(":/img/img/storage_0.png");
  storage_btn->setHoveredPixmap(":/img/img/storage_1.png");

  ////main layout
  main_layout = new QVBoxLayout(this);
  main_layout->setContentsMargins(30,20,20,0);
  main_layout->setSpacing(20);
  main_layout->setAlignment(Qt::AlignTop);
  main_layout->addWidget(welcome_btn);
  main_layout->addWidget(storage_btn);
  ///For test period!
  storage_btn->setHidden(true);

  this->setParent(parent);

}

GuiHomeTab::~GuiHomeTab()
{

}

