#include "HomeTab.h"

HomeTab::HomeTab(QWidget *parent) : QWidget(parent)
{
  welcome_btn = new MenuButton("welcome", GUI::StaticStackType::Home_Welcome, this);
  list_btn = new MenuButton("online user", GUI::StaticStackType::Home_list, this);
  storage_btn = new MenuButton("file storage", GUI::StaticStackType::Home_Storage, this);

  welcome_btn->setDefaultPixmap(":/img/img/welcome_0.png");
  welcome_btn->setHoveredPixmap(":/img/img/welcome_1.png");

  list_btn->setDefaultPixmap(":/img/img/list_0");
  list_btn->setHoveredPixmap(":/img/img/list_1");

  storage_btn->setDefaultPixmap(":/img/img/storage_0.png");
  storage_btn->setHoveredPixmap(":/img/img/storage_1.png");

  button_layout = new QVBoxLayout();
  button_layout->setContentsMargins(30,20,20,0);
  button_layout->addWidget(welcome_btn);
  button_layout->addWidget(list_btn);
  button_layout->addWidget(storage_btn);

  QLabel *bkg = new QLabel();
  bkg->setPixmap(QPixmap(":/img/img/corner_honey.png"));
  bkg->setAlignment(Qt::AlignBottom | Qt::AlignLeft);

  ////main layout
  main_layout = new QVBoxLayout(this);
  main_layout->setContentsMargins(0,0,0,0);
  main_layout->setSpacing(20);
  main_layout->setAlignment(Qt::AlignTop);
  main_layout->addLayout(button_layout);
  main_layout->addWidget(bkg,Qt::AlignBaseline);
//  main_layout->addWidget(welcome_btn);
//  main_layout->addWidget(list_btn);
//  main_layout->addWidget(storage_btn);
  ///For test period!
  storage_btn->setHidden(true);

  this->setParent(parent);

}

HomeTab::~HomeTab()
{

}

