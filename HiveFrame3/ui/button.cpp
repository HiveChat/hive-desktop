#include "button.h"

Button::Button(const QString &txt, int w, int h, QWidget *parent)
  : QOpenGLWidget(parent)
  , width(w)
  , height(h)
  , text(txt)
{
  setFont("Gill Sans Light", 14);
  setText(txt);
  this->setFixedSize(QSize(w,h));
  this->setAutoFillBackground(true);
}

Button::Button(const QString &txt, QWidget *parent)
  : QOpenGLWidget(parent)
{
  setFont("Gill Sans Light", 13);
  setText(txt);
//  this->setMinimumSize(QSize(width, height));
  this->setAutoFillBackground(true);
}

void Button::setFont(const QFont &font)
{

}

void Button::setFont(const QString &family, const int &pixelSize)
{
  font.setFamily(family);
  font.setPixelSize(14);
  updateTextRect();
}

void Button::setText(const QString &str)
{
  text = str;
  updateTextRect();
}

void Button::paintEvent(QPaintEvent *)
{
  QPainter painter;
  painter.begin(this);
  painter.setPen(Qt::NoPen);
  painter.setBrush(QBrush(hovered ? background_hovered_color :background_default_color, Qt::SolidPattern));
  painter.setRenderHint(QPainter::Antialiasing,true);
  painter.drawRoundedRect(QRect(1, (this->rect().height() - height) * 0.5, this->rect().width() - 1, height - 1),10,10);
  QTextOption textOption;
  textOption.setAlignment(Qt::AlignCenter);
  textOption.setWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);
  painter.setFont(font);
  painter.setPen(hovered ? foreground_hovered_color : foreground_default_color);
  painter.drawText(this->rect(), text, textOption);
  painter.end();
}

void Button::mousePressEvent(QMouseEvent *)
{

}

void Button::mouseReleaseEvent(QMouseEvent *)
{
  emit clicked();
}

void Button::enterEvent(QEvent *)
{
  hovered = true;
  this->update();
}

void Button::leaveEvent(QEvent *)
{
  hovered = false;
  this->update();
}

void Button::updateTextRect()
{
  QFontMetrics metrics(font);
  width = metrics.width(text) + 40;
  update();
}


