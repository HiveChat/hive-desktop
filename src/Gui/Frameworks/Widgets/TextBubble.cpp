#include "TextBubble.h"

TextBubble_text_area::TextBubble_text_area(const QString &text, const bool alignLeft = true, QWidget *parent)
  : QWidget(parent)
{
  int maxWidth = 500;

  //QString message = text+"\n";//"<p style=\"line-height:100%\">" + text + "</p>";
  label = new QLabel(this);
  label->setText(text);
  label->setFont(Global::font_chatBubble);
  label->adjustSize();
  label->setWordWrap(true);
  label->setTextInteractionFlags(Qt::TextSelectableByMouse);
  label->setCursor(QCursor(Qt::IBeamCursor));

  main_layout = new QHBoxLayout(this);
  main_layout->setContentsMargins(10,10,10,15);
  main_layout->addWidget(label);

  if(alignLeft)
    {
      color = &Global::settings.chat_bubble_color_i;//255,181,0
      main_layout->setAlignment(Qt::AlignLeft);
    }
  else
    {
      color = &Global::settings.chat_bubble_color_o;//255,215,126
      main_layout->setAlignment(Qt::AlignRight);
    }

  this->setFixedWidth(maxWidth);
}

void TextBubble_text_area::paintEvent(QPaintEvent *)
{
  label->adjustSize();
  int width = label->rect().width() + 20;
  int height = label->rect().height() + 20;
  QPainter painter(this);
  painter.setPen(QPen(Qt::NoPen));
  painter.setBrush(QBrush(*color, Qt::SolidPattern));
  painter.drawRoundedRect(label->x() - 10
                          , label->y() - 10
                          , width
                          , height
                          , 12
                          , 12);
  this->setFixedSize(width, height);
}

TextBubble::TextBubble(const QString &text, bool alignLeft = true, QWidget *parent)
  : QWidget(parent)
{
  text_area = new TextBubble_text_area(text, alignLeft, this);

  main_layout = new QHBoxLayout(this);
  main_layout->setContentsMargins(0,0,0,0);
  main_layout->setSpacing(10);

  if(alignLeft)
    {
      main_layout->setAlignment(Qt::AlignLeft);
      main_layout->addWidget(text_area);
    }
  else
    {
      main_layout->setAlignment(Qt::AlignRight);
      main_layout->addWidget(text_area);
    }
}





FileBubble_file_info::FileBubble_file_info(const QString &text, const bool alignLeft = true, QWidget *parent)
  : QLabel(parent)
{
  int maxWidth = 500;

  //QString message = text+"\n";//"<p style=\"line-height:100%\">" + text + "</p>";
  QPixmap file_icon(":/icon/icon/doc.png");
  file_icon.setDevicePixelRatio(Global::window_dpr);
  label =  new QLabel(this);
  label->setPixmap(file_icon);
//  label->adjustSize();
//  label->setWordWrap(true);
//  label->setTextInteractionFlags(Qt::TextSelectableByMouse);
//  label->setCursor(QCursor(Qt::IBeamCursor));

  main_layout = new QHBoxLayout(this);
  main_layout->setContentsMargins(10,10,10,15);
  main_layout->addWidget(label);

  if(alignLeft)
    {
      color = &Global::settings.chat_bubble_color_i;//255,181,0
      main_layout->setAlignment(Qt::AlignLeft);
    }
  else
    {
      color = &Global::settings.chat_bubble_color_o;//255,215,126
      main_layout->setAlignment(Qt::AlignRight);
    }

  this->setFixedWidth(maxWidth);
}

void FileBubble_file_info::paintEvent(QPaintEvent *)
{
  label->adjustSize();

  QPainter painter(this);
  painter.setPen(QPen(Qt::NoPen));
  //color options:
  //255,197,28,100
  //255,215,126
  painter.setBrush(QBrush(*color, Qt::SolidPattern));
  painter.drawRoundedRect(label->x()-10,label->y()-10,label->rect().width()+20,label->rect().height()+20,12,12);
  this->setFixedWidth(label->rect().width()+20);
  this->setFixedHeight(label->rect().height()+20);

}


FileBubble::FileBubble(const QString &text, const bool alignLeft = true, QWidget *parent) : QWidget(parent)
{
  file_info = new FileBubble_file_info(text, alignLeft, this);

  main_layout = new QHBoxLayout(this);
  main_layout->setContentsMargins(0,0,0,0);
  main_layout->setSpacing(10);

  if(alignLeft)
    {
      main_layout->setAlignment(Qt::AlignLeft);
      main_layout->addWidget(file_info);
    }
  else
    {
      main_layout->setAlignment(Qt::AlignRight);
      main_layout->addWidget(file_info);
    }
}


