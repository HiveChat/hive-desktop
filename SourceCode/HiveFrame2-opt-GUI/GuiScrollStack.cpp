#include "GuiScrollStack.h"

GuiScrollStack::GuiScrollStack(QWidget *parent) : QWidget(parent)
{
  QPalette palette;
  palette.setColor(QPalette::Window, QColor(255,255,255));

  ///top widget
  QWidget *top_widget = new QWidget(this);

  icon_btn = new GuiAvatarButton("", 90, this);
  icon_btn->setAlignment(Qt::AlignLeft);

  title_label = new QLabel("", this);
  sub_title_label = new QLabel("", this);

  QFont usr_name_font("Futura");//Verdana
  usr_name_font.setPointSize(15);
  title_label->setFont(usr_name_font);

  QFont usr_ip_font("Futura");//Gill Sans
  usr_ip_font.setPointSize(12);
  sub_title_label->setFont(usr_ip_font);

  QVBoxLayout *title_layout = new QVBoxLayout();
  title_layout->setContentsMargins(0,0,10,10);
  title_layout->addWidget(title_label);
  title_layout->addWidget(sub_title_label);

  top_widget_main_layout = new QHBoxLayout(top_widget);
  top_widget_main_layout->setAlignment(Qt::AlignLeft);
  top_widget_main_layout->setContentsMargins(15,10,10,0);
  top_widget_main_layout->setSpacing(10);
  top_widget_main_layout->addWidget(icon_btn);
  top_widget_main_layout->addLayout(title_layout);

  top_widget->setPalette(palette);
  top_widget->setAutoFillBackground(true);
  top_widget->setFixedHeight(69);

  ///!top widget

  ///central widget
  QWidget *mid_widget = new QWidget(this);

  central_layout = new QFormLayout();
  central_layout->setAlignment(Qt::AlignTop |Qt::AlignLeft);
  central_layout->setContentsMargins(10,30,10,30);

  QFrame *top_line = new QFrame(this);
  top_line->setFrameShape(QFrame::HLine);
  top_line->setFrameShadow(QFrame::Plain);
  top_line->setFixedHeight(2);
  top_line->setStyleSheet ("QFrame{  background: #ffd77e; border: 0px transparent;  }");

  QFrame *bottom_line = new QFrame(this);
  bottom_line->setFrameShape(QFrame::HLine);
  bottom_line->setFrameShadow(QFrame::Plain);
  bottom_line->setFixedHeight(4);
  bottom_line->setStyleSheet ("QFrame{  background: #ffb500; border: 0px transparent;  }");

  QVBoxLayout *mid_widget_layout = new QVBoxLayout(this);
  mid_widget_layout->setAlignment(Qt::AlignTop);
  mid_widget_layout->setSpacing(5);
  mid_widget_layout->setContentsMargins(0,0,0,0);
  mid_widget_layout->addWidget(top_line);
  mid_widget_layout->addLayout(central_layout);
  mid_widget_layout->addStretch();
  mid_widget_layout->addWidget(bottom_line);

  mid_widget->setPalette(palette);
  mid_widget->setLayout(mid_widget_layout);
  ///!central widget

  QScrollArea *scroll_area = new QScrollArea(this);
  scroll_area->setWidgetResizable(true);
  scroll_area->setWidget(mid_widget);
  scroll_area->setFrameStyle(0);


  ////main layout
  QVBoxLayout *main_layout = new QVBoxLayout(this);
  main_layout->setAlignment(Qt::AlignTop);
  main_layout->addWidget(top_widget);
  main_layout->addWidget(scroll_area);
  main_layout->setMargin(0);
  main_layout->setSpacing(0);

  this->setParent(parent);
}

GuiScrollStack::~GuiScrollStack()
{

}

void GuiScrollStack::setTitle(QString text)
{
  title_label->setText(text);
}

void GuiScrollStack::setSubTitle(QString text)
{
  sub_title_label->setText(text);
}

void GuiScrollStack::setIcon(QString path)
{
  icon_btn->setAvatar(path);
}



