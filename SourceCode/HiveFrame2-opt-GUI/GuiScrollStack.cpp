#include "GuiScrollStack.h"




GuiScrollStack::GuiScrollStack(QString imgPath, QString title, QString subTitle, QWidget *centralWidget, QWidget *parent) : QWidget(parent)
{
  QPalette palette;
  palette.setColor(QPalette::Window, QColor(255,255,255));

  ///top widget
  QWidget *top_widget = new QWidget(this);

  GuiAvatarButton *icon_btn = new GuiAvatarButton(imgPath, 90, this);
  icon_btn->setFixedHeight(50);
  icon_btn->setAlignment(Qt::AlignLeft);

  QLabel *title_label = new QLabel(title, this);
  QLabel *sub_title_label = new QLabel(subTitle, this);

  QFont usr_name_font("Futura");//Verdana
  usr_name_font.setPointSize(15);
  title_label->setFont(usr_name_font);

  QFont usr_ip_font("Futura");//Gill Sans
  usr_ip_font.setPointSize(11);
  sub_title_label->setFont(usr_ip_font);

  QVBoxLayout *usr_info_layout = new QVBoxLayout();
  usr_info_layout->setContentsMargins(0,0,10,10);
  usr_info_layout->addWidget(title_label);
  usr_info_layout->addWidget(sub_title_label);

  QHBoxLayout *top_widget_main_layout = new QHBoxLayout(top_widget);
  top_widget_main_layout->setAlignment(Qt::AlignLeft);
  top_widget_main_layout->setContentsMargins(15,10,10,0);
  top_widget_main_layout->setSpacing(10);
  top_widget_main_layout->addWidget(icon_btn);
  top_widget_main_layout->addLayout(usr_info_layout);

  top_widget->setPalette(palette);
  top_widget->setAutoFillBackground(true);
  top_widget->setFixedHeight(67);

  ///!top widget

  ///central widget
  QWidget *central_widget = new QWidget(this);

  QFrame *bottom_line = new QFrame(this);
  bottom_line->setFrameShape(QFrame::HLine);
  bottom_line->setFrameShadow(QFrame::Plain);
  bottom_line->setFixedHeight(4);
  bottom_line->setStyleSheet ("QFrame{  background: #ffb500; border: 0px transparent;  }");

  QFrame *top_line = new QFrame(this);
  top_line->setFrameShape(QFrame::HLine);
  top_line->setFrameShadow(QFrame::Plain);
  top_line->setFixedHeight(4);
  top_line->setStyleSheet ("QFrame{  background: #ffd77e; border: 0px transparent;  }");

  QVBoxLayout *central_widget_layout = new QVBoxLayout(central_widget);
  central_widget_layout->setAlignment(Qt::AlignTop);
  central_widget_layout->setSpacing(5);
  central_widget_layout->setContentsMargins(0,0,0,0);
  central_widget_layout->addWidget(top_line);
  central_widget_layout->addWidget(centralWidget);
  central_widget_layout->addWidget(bottom_line);

  central_widget->setPalette(palette);

  ///!central widget

  QScrollArea *scroll_area = new QScrollArea(this);
  scroll_area->setWidgetResizable(true);
  scroll_area->setWidget(central_widget);
  scroll_area->setFrameStyle(0);


  ////main layout
  QVBoxLayout *main_layout = new QVBoxLayout(this);
  main_layout->setAlignment(Qt::AlignCenter);
  main_layout->addWidget(top_widget);
  main_layout->addWidget(central_widget);
  main_layout->setMargin(0);
  main_layout->setSpacing(0);

  this->setParent(parent);


}

GuiScrollStack::~GuiScrollStack()
{

}



