#include "Gui/Frameworks/ScrollStack.h"
#include <QDebug>

ScrollStack::ScrollStack(QWidget *parent) : QWidget(parent)
{
}

ScrollStack::~ScrollStack()
{

}

void ScrollStack::setTitle(const QString &text)
{
  if(text.isEmpty() || text.isNull())
    {
      qDebug()<<"#GuiScrollStack::setTitle(): Empty title";
      return;
    }
  title_qstr = text;

  if(layout_style == LayoutStyle::Linear)
    {
      composite_title_label->setText(title_qstr+" - "+sub_title_qstr);
    }
  else if(layout_style == LayoutStyle::Profile)
    {
      title_label->setText(title_qstr);
    }
}

void ScrollStack::setSubTitle(const QString &text)
{
  if(text.isNull() || text.isEmpty())
    {
      qDebug()<<"GuiScrollStack::setSubTitle(): Empty subtitle";
      return;
    }
  sub_title_qstr = text;

  if(layout_style == LayoutStyle::Linear)
    {
      composite_title_label->setText(title_qstr+" - "+sub_title_qstr);
    }
  else if(layout_style == LayoutStyle::Profile)
    {
      sub_title_label->setText(sub_title_qstr);
    }

}

void ScrollStack::setIcon(const QString &path)
{
  if(path.isNull() || path.isEmpty())
    {
      return;
    }
  icon_btn->setAvatar(path);
}

void ScrollStack::setUpUI(const LayoutStyle &layoutStyle)//////add enum GUI switcher.
{
  layout_style = layoutStyle;

  text_palette.setColor(QPalette::WindowText, QColor(100,100,100));
  sub_text_palette.setColor(QPalette::WindowText, QColor(100,100,100/*130, 130, 130*/));

  QPalette palette;
  palette.setColor(QPalette::Window, QColor(255,255,255));


  ///top widget
  QFrame *top_frame = new QFrame(this);
  top_frame->setPalette(palette);
  top_frame->setAutoFillBackground(true);
  top_frame->setFixedHeight(69);

  icon_btn = new GuiAvatarButton(90, this);
  icon_btn->setAlignment(Qt::AlignLeft);

  top_frame_main_layout = new QHBoxLayout(top_frame);
  top_frame_main_layout->setAlignment(Qt::AlignLeft |Qt::AlignVCenter);
  top_frame_main_layout->addWidget(icon_btn);

  if(layout_style == LayoutStyle::Linear)
    {
      composite_title_label = new QLabel(this);
      composite_title_label->setPalette(text_palette);
      composite_title_label->setFont(GlobalData::font_scrollStackTitle);

      top_frame_main_layout->setContentsMargins(15,0,10,0);
      top_frame_main_layout->addWidget(composite_title_label);
    }
  else if(layout_style == LayoutStyle::Profile)
    {
      title_label = new QLabel(this);
      title_label->setFont(GlobalData::font_scrollStackTitle);

      sub_title_label = new QLabel(this);
      sub_title_label->setFont(GlobalData::font_scrollStackSubtitle);

      QVBoxLayout *usr_info_layout = new QVBoxLayout();
      usr_info_layout->setContentsMargins(0,0,10,10);
      usr_info_layout->addWidget(title_label);
      usr_info_layout->addWidget(sub_title_label);

      top_frame_main_layout->setContentsMargins(15,10,10,0);
      top_frame_main_layout->addLayout(usr_info_layout);
    }

  QFrame *topwidget_base_line = new QFrame(this);
  topwidget_base_line->setFrameShape(QFrame::HLine);
  topwidget_base_line->setFrameShadow(QFrame::Plain);
  topwidget_base_line->setFixedHeight(2);
  topwidget_base_line->setStyleSheet ("QFrame{  background: #ffd77e; border: 0px transparent;  }");

  ///!top widget

  ///central widget
  QFrame *mid_frame = new QFrame(this);

  central_layout = new QVBoxLayout();
  central_layout->setAlignment(Qt::AlignCenter);
  central_layout->setContentsMargins(30,20,0,50);
  central_layout->setSpacing(0);

  QFrame *scroll_top_line = new QFrame(this);
  scroll_top_line->setFrameShape(QFrame::HLine);
  scroll_top_line->setFrameShadow(QFrame::Plain);
  scroll_top_line->setFixedHeight(1);
  scroll_top_line->setStyleSheet ("QFrame{  background: #ffd77e; border: 0px transparent;  }");

  QFrame *scroll_bottom_line = new QFrame(this);
  scroll_bottom_line->setFrameShape(QFrame::HLine);
  scroll_bottom_line->setFrameShadow(QFrame::Plain);
  scroll_bottom_line->setFixedHeight(4);
  scroll_bottom_line->setStyleSheet("QFrame{  background: #ffb500; border: 0px transparent;  }");

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

  scroll_area = new QScrollArea(this);
  scroll_area->setWidgetResizable(true);
  scroll_area->setWidget(mid_frame);
  scroll_area->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  scroll_area->setFrameStyle(0);


  ////main layout
  main_layout = new QVBoxLayout(this);
  main_layout->setAlignment(Qt::AlignTop);
  main_layout->addWidget(top_frame);
  main_layout->addWidget(topwidget_base_line);
  main_layout->addWidget(scroll_area);
  main_layout->setMargin(0);
  main_layout->setSpacing(0);

}

QLabel *ScrollStack::addTag(const QString &text)
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

  central_layout->addSpacing(25);
  central_layout->addWidget(tag_labe);
  central_layout->addWidget(line);

  return tag_labe;
}

QBoxLayout *ScrollStack::addItem(const QString &text, const QString &string, const bool &wrapping)
{
  QLabel *text_label = new QLabel("\t" + text, this);
  text_label->setFont(GlobalData::font_scrollStackSubtitle);
  text_label->setPalette(sub_text_palette);

  QLabel *string_label = new QLabel(string, this);
#ifdef Q_OS_WIN
  string_label->setFont(GlobalData::font_scrollStackSubtitle);
#endif
  string_label->setWordWrap(wrapping);
  string_label->adjustSize();

  QHBoxLayout *layout = new QHBoxLayout();
  layout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
  layout->setSizeConstraint(QLayout::SetFixedSize);
  layout->setContentsMargins(0,10,200,0);
  layout->setSpacing(80);
  layout->addWidget(text_label);
  layout->addWidget(string_label);

  central_layout->addSpacing(10);
  central_layout->addLayout(layout);

  return layout;
}

QBoxLayout *ScrollStack::addItem(const QString &text, QWidget *widget)
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

  central_layout->addSpacing(10);
  central_layout->addLayout(layout);

  return layout;
}

QBoxLayout *ScrollStack::addItem(QWidget *widget, const QString &text)
{
  QLabel *text_label = new QLabel(text, this);
  text_label->setFont(GlobalData::font_scrollStackSubtitle);
  text_label->setPalette(sub_text_palette);

  QHBoxLayout *layout = new QHBoxLayout();
  layout->setContentsMargins(0,10,200,0);
  layout->setSpacing(30);
  layout->setStretch(0,0);
  layout->addSpacing(60);
  layout->addWidget(widget);
  layout->addWidget(text_label);

  central_layout->addSpacing(10);
  central_layout->addLayout(layout);

  return layout;
}

QBoxLayout *ScrollStack::addItem(const QString &text, QLayout *widgetLayout)
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

  central_layout->addSpacing(10);
  central_layout->addLayout(layout);

  return layout;
}

void ScrollStack::addItem(QWidget *centralWidget)
{
  central_layout->addWidget(centralWidget);
  central_layout->setAlignment(Qt::AlignCenter);
  central_layout->setMargin(0);
  central_layout->setSpacing(0);
}



