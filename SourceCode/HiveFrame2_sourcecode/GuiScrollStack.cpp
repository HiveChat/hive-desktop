#include "GuiScrollStack.h"
#include <QDebug>

GuiScrollStack::GuiScrollStack(QWidget *parent) : QWidget(parent)
{
  setUpUI();
}

GuiScrollStack::~GuiScrollStack()
{

}

void GuiScrollStack::setTitle(const QSting &text)
{
  title_qstr = text;
  title_label->setText(title_qstr+" - "+sub_title_qstr);
}

void GuiScrollStack::setSubTitle(const QSting &text)
{
  sub_title_qstr = text;
  title_label->setText(title_qstr+" - "+sub_title_qstr);
}

void GuiScrollStack::setIcon(const QSting &path)
{
  icon_btn->setAvatar(path);
}

void GuiScrollStack::setUpUI()
{
  text_palette.setColor(QPalette::WindowText, QColor(100,100,100));
  sub_text_palette.setColor(QPalette::WindowText, QColor(100,100,100/*130, 130, 130*/));

  QPalette palette;
  palette.setColor(QPalette::Window, QColor(255,255,255));

  ///top widget
  QFrame *top_frame = new QFrame(this);

  icon_btn = new GuiAvatarButton(90, this);
  icon_btn->setAlignment(Qt::AlignLeft);

  title_label = new QLabel("", this);
  title_label->setPalette(text_palette);
  title_label->setFont(GlobalData::font_scrollStackTitle);

  top_frame_main_layout = new QHBoxLayout(top_frame);
  top_frame_main_layout->setAlignment(Qt::AlignLeft |Qt::AlignVCenter);
  top_frame_main_layout->setContentsMargins(15,0,10,0);
  top_frame_main_layout->addWidget(icon_btn);
  top_frame_main_layout->addWidget(title_label);

  top_frame->setPalette(palette);
  top_frame->setAutoFillBackground(true);
  top_frame->setFixedHeight(69);

  ///!top widget

  ///central widget
  QFrame *mid_frame = new QFrame(this);

  central_layout = new QVBoxLayout();
  central_layout->setAlignment(Qt::AlignCenter);
  central_layout->setContentsMargins(30,30,0,50);
  central_layout->setSpacing(0);

  QFrame *scroll_top_line = new QFrame(this);
  scroll_top_line->setFrameShape(QFrame::HLine);
  scroll_top_line->setFrameShadow(QFrame::Plain);
  scroll_top_line->setFixedHeight(2);
  scroll_top_line->setStyleSheet ("QFrame{  background: #ffd77e; border: 0px transparent;  }");

  QFrame *scroll_bottom_line = new QFrame(this);
  scroll_bottom_line->setFrameShape(QFrame::HLine);
  scroll_bottom_line->setFrameShadow(QFrame::Plain);
  scroll_bottom_line->setFixedHeight(4);
  scroll_bottom_line->setStyleSheet ("QFrame{  background: #ffb500; border: 0px transparent;  }");

  QVBoxLayout *mid_frame_layout = new QVBoxLayout(this);
  mid_frame_layout->setAlignment(Qt::AlignTop);
  mid_frame_layout->setSpacing(5);
  mid_frame_layout->setContentsMargins(0,0,0,0);
  mid_frame_layout->addWidget(scroll_top_line);
  mid_frame_layout->addLayout(central_layout);
  mid_frame_layout->addStretch();
  mid_frame_layout->addWidget(scroll_bottom_line);

  mid_frame->setPalette(palette);
  mid_frame->setLayout(mid_frame_layout);
  ///!central widget

  QScrollArea *scroll_area = new QScrollArea(this);
  scroll_area->setWidgetResizable(true);
  scroll_area->setWidget(mid_frame);
  scroll_area->setFrameStyle(0);


  ////main layout
  QVBoxLayout *main_layout = new QVBoxLayout(this);
  main_layout->setAlignment(Qt::AlignTop);
  main_layout->addWidget(top_frame);
  main_layout->addWidget(scroll_area);
  main_layout->setMargin(0);
  main_layout->setSpacing(0);

}

void GuiScrollStack::addTag(QString text)
{
  QLabel *tag_labe = new QLabel(text, this);
  tag_labe->setFont(GlobalData::font_scrollStackTitle);
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

void GuiScrollStack::addItem(const QString &text, QString string)
{
  QLabel *text_label = new QLabel("\t" + text, this);
  text_label->setFont(GlobalData::font_scrollStackSubtitle);
  text_label->setPalette(sub_text_palette);

  QLabel *string_label = new QLabel(string, this);
  string_label->setWordWrap(true);
  string_label->adjustSize();

  QHBoxLayout *layout = new QHBoxLayout();
  layout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
  layout->setSizeConstraint(QLayout::SetFixedSize);
  layout->setContentsMargins(0,10,200,0);
  layout->setSpacing(30);
  layout->addWidget(text_label);
  layout->addWidget(string_label);

  central_layout->addLayout(layout);
  central_layout->addSpacing(10);
}

void GuiScrollStack::addItem(const QString &text, QWidget *widget)
{
  QLabel *text_label = new QLabel(text, this);
  text_label->setFont(GlobalData::font_scrollStackSubtitle);
  text_label->setPalette(sub_text_palette);

  QHBoxLayout *layout = new QHBoxLayout();
  layout->setContentsMargins(0,10,200,0);
  layout->setSpacing(30);
  layout->setStretch(0,0);
  layout->addWidget(text_label);
  layout->addWidget(widget);

  central_layout->addLayout(layout);
  central_layout->addSpacing(10);

}

void GuiScrollStack::addItem(const QString &text, QLayout *widgetLayout)
{
  QLabel *text_label = new QLabel(text, this);
  text_label->setFont(GlobalData::font_scrollStackSubtitle);
  text_label->setPalette(sub_text_palette);

  QHBoxLayout *layout = new QHBoxLayout();
  layout->setContentsMargins(0,10,200,0);
  layout->setSpacing(30);
  layout->setStretch(0,0);
  layout->addWidget(text_label);
  layout->addLayout(widgetLayout);

  central_layout->addLayout(layout);
  central_layout->addSpacing(10);

}

void GuiScrollStack::addItem(QWidget *centralWidget)
{
  central_layout->addWidget(centralWidget);
  central_layout->setAlignment(Qt::AlignCenter);
  central_layout->setMargin(0);
  central_layout->setSpacing(0);
}



