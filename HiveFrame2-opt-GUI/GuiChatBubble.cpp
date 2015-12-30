#include "GuiChatBubble.h"

GuiChatBubble_text_area::GuiChatBubble_text_area(QString text, int maxWidth, QWidget *parent)
{

  QFont font("Verdana");
  font.setPixelSize(14);

  label =  new QLabel(text);
  label->setFont(font);
  label->adjustSize();
  label->setWordWrap(true);
  label->setTextInteractionFlags(Qt::TextSelectableByMouse);
  label->setCursor(QCursor(Qt::IBeamCursor));

  main_layout = new QHBoxLayout(this);
  main_layout->setContentsMargins(10,10,10,15);
  main_layout->addWidget(label);

  this->setParent(parent);
  this->setFixedWidth(maxWidth);
  qDebug()<<label->width();
  qDebug()<<label->height();
}

void GuiChatBubble_text_area::paintEvent(QPaintEvent *)
{
  QPainter painter(this);
  painter.setPen(QPen(Qt::NoPen));
  painter.setBrush(QBrush(QColor(255,181,0),Qt::SolidPattern));
  painter.drawRoundedRect(0,0,label->rect().width()+20,label->rect().height()+20,12,12);
}


GuiChatBubble::GuiChatBubble(QString text, bool alignLeft = true, QWidget *parent) : QWidget(parent)
{
  strip_pixmap.load("/Users/Echo/Desktop/asp.png");
  strip_pixmap.setDevicePixelRatio(2.0);
  strip = new QLabel();
  strip->setPixmap(strip_pixmap);
  strip->setAlignment(Qt::AlignTop);
  strip->setContentsMargins(0,10,0,0);

  text_area = new GuiChatBubble_text_area(text, 400,this);

  main_layout = new QHBoxLayout(this);
  main_layout->setAlignment(Qt::AlignLeft);
  main_layout->setContentsMargins(0,0,0,0);
  main_layout->setSpacing(0);
  main_layout->addWidget(strip);
  main_layout->addWidget(text_area);


  this->setParent(parent);
  //this->setFixedHeight(button->height()+20);

}
