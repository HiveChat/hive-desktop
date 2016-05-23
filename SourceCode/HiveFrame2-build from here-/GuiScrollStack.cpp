#include "GuiScrollStack.h"
#include <QDebug>

GuiScrollStack::GuiScrollStack(QWidget *parent) : QWidget(parent)
{
  setUpUI();
  this->setParent(parent);
}

GuiScrollStack::~GuiScrollStack()
{

}

void GuiScrollStack::setTitle(QString text)
{
  title_qstr = text;
  title_label->setText(title_qstr+" - "+sub_title_qstr);
}

void GuiScrollStack::setSubTitle(QString text)
{
  sub_title_qstr = text;
  title_label->setText(title_qstr+" - "+sub_title_qstr);
}

void GuiScrollStack::setIcon(QString path)
{
  icon_btn->setAvatar(path);
}

void GuiScrollStack::setUpUI()
{
  text_palette.setColor(QPalette::WindowText, QColor(80,80,80));
  sub_text_palette.setColor(QPalette::WindowText, QColor(130, 130, 130));

  QPalette palette;
  palette.setColor(QPalette::Window, QColor(255,255,255));

  ///top widget
  QWidget *top_widget = new QWidget(this);

  icon_btn = new GuiAvatarButton(90, this);
  icon_btn->setAlignment(Qt::AlignLeft);

  title_label = new QLabel("", this);
  title_label->setPalette(text_palette);

  top_widget_main_layout = new QHBoxLayout(top_widget);
  top_widget_main_layout->setAlignment(Qt::AlignLeft |Qt::AlignVCenter);
  top_widget_main_layout->setContentsMargins(15,0,10,0);
  top_widget_main_layout->addWidget(icon_btn);
  top_widget_main_layout->addWidget(title_label);

  top_widget->setPalette(palette);
  top_widget->setAutoFillBackground(true);
  top_widget->setFixedHeight(69);

  ///!top widget

  ///central widget
  QWidget *mid_widget = new QWidget(this);

  central_layout = new QVBoxLayout();
//  central_layout->setAlignment(Qt::AlignTop |Qt::AlignLeft);
//  central_layout->setContentsMargins(10,30,10,30);
  central_layout->setAlignment(Qt::AlignCenter);
  central_layout->setContentsMargins(30,30,0,50);
  central_layout->setSpacing(0);

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

}

void GuiScrollStack::addTag(QString text)
{
  QLabel *tag_labe = new QLabel(text, this);
  tag_labe->setFont(font);
  tag_labe->setPalette(text_palette);

  QFrame *line = new QFrame(this);
  line->setFrameShape(QFrame::HLine);
  line->setFrameShadow(QFrame::Plain);
  line->setFixedHeight(1);
  line->setFixedWidth(580);
  line->setStyleSheet ("QFrame{  background: #CFCFCF; border: 0px transparent;  }");

  central_layout->addWidget(tag_labe);
  central_layout->addWidget(line);
  central_layout->addSpacing(30);
}

void GuiScrollStack::addItem(QString text, QString string)
{
  QLabel *text_label = new QLabel("\t" + text, this);
  text_label->setFont(sub_font);
  text_label->setPalette(sub_text_palette);

  QLabel *string_label = new QLabel(string, this);
  string_label->setWordWrap(true);
//  string_label->setSizePolicy(QSizePolicy::Fixed);
  //string_label->setSizePolicy(QSizePolicy::Fixed);
  string_label->adjustSize();

  QHBoxLayout *layout = new QHBoxLayout();
  layout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
  layout->setSizeConstraint(QLayout::SetFixedSize);
  layout->setContentsMargins(0,10,200,0);
  layout->setSpacing(30);
//  layout->setStretch(0,0);
  layout->addWidget(text_label);
  layout->addWidget(string_label);

  central_layout->addLayout(layout);
  central_layout->addSpacing(10);
}

void GuiScrollStack::addItem(QString text, QWidget *widget)
{
  QLabel *text_label = new QLabel(text, this);
  text_label->setFont(sub_font);
  text_label->setPalette(sub_text_palette);

  QHBoxLayout *layout = new QHBoxLayout();
//  layout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
  layout->setContentsMargins(0,10,200,0);
  layout->setSpacing(30);
  layout->setStretch(0,0);
  layout->addWidget(text_label);
  layout->addWidget(widget);

  central_layout->addLayout(layout);
  central_layout->addSpacing(10);

}

void GuiScrollStack::addItem(QString text, QLayout *widgetLayout)
{
  QLabel *text_label = new QLabel(text, this);
  text_label->setFont(sub_font);
  text_label->setPalette(sub_text_palette);

  QHBoxLayout *layout = new QHBoxLayout();
//  layout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
  layout->setContentsMargins(0,10,200,0);
  layout->setSpacing(30);
  layout->setStretch(0,0);
  layout->addWidget(text_label);
  layout->addLayout(widgetLayout);

  central_layout->addLayout(layout);
  central_layout->addSpacing(10);

}



