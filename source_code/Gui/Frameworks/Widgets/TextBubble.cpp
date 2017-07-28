#include "TextBubble.h"

TextBubble::TextBubble(const QString &txt, int w, int h, QWidget *parent)
  : QWidget(parent)
  , width(w)
  , height(h)
  , text(txt)
{
  setFont("Gill Sans Light", 13);
  setText(txt);
  this->setFixedSize(QSize(w,h));
  this->setAutoFillBackground(false);
}

TextBubble::TextBubble(const QString &txt, QWidget *parent)
  : QWidget(parent)
{
  setFont("Gill Sans Light", 13);
  setText(txt);
  this->setMinimumSize(QSize(width, height));
  this->setAutoFillBackground(false);
}

void TextBubble::setFont(const QFont &f)
{
  font = f;
  updateTextRect();

}

void TextBubble::setFont(const QString &family, const int &pixelSize)
{
  font.setFamily(family);
  font.setPixelSize(14);
  updateTextRect();
}

void TextBubble::setText(const QString &str)
{
  text = str;
  updateTextRect();
}

void TextBubble::setPalette(const TextBubble::Palette &palette, const QColor &color)
{
  switch (palette) {
    case Palette::BackgroundDefault:
      {
        background_default_color = color;
        break;
      }
    case Palette::ForegroundDefault:
      {
        foreground_default_color = color;
        break;
      }
    default:
      break;
    }
}

void TextBubble::paintEvent(QPaintEvent *)
{
  QPainter painter;
  painter.begin(this);
  painter.setPen(Qt::NoPen);
  painter.setBrush(QBrush(background_default_color, Qt::SolidPattern));
  painter.setRenderHint(QPainter::Antialiasing,true);
  painter.drawRoundedRect(background_rect,5,5);
  QTextOption textOption;
  textOption.setAlignment(Qt::AlignLeft);
  textOption.setWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);
  painter.setFont(font);
  painter.setPen(foreground_default_color);
  painter.drawText(QRect(background_rect.x()+5, background_rect.y()+5, background_rect.width()-10, background_rect.height()-10), text, textOption);
//  if (painter.paintEngine()->type() != QPaintEngine::OpenGL2) {
//          qWarning("OpenGLScene: drawBackground needs a QGLWidget to be set as viewport on the graphics view");
//          qDebug()<<painter.paintEngine()->type();
//          return;
//      }
  painter.end();
}

void TextBubble::resizeEvent(QResizeEvent *ev)
{
  background_rect = QRect(1, 1, width + 2, height + 2);
  QWidget::resizeEvent(ev);
}

void TextBubble::mousePressEvent(QMouseEvent *)
{

}

void TextBubble::mouseReleaseEvent(QMouseEvent *)
{
  emit clicked();
}

//void TextBubble::enterEvent(QEvent *ev)
//{
//  hovered = true;
//  this->update();
//}

//void TextBubble::leaveEvent(QEvent *ev)
//{
//  hovered = false;
//  this->update();
//}

void TextBubble::updateTextRect()
{
  QFontMetrics metrics(font);

  int lineCount = 0;

  do
    {
      width = metrics.width(text) + 15 - lineCount * max_width;
      lineCount ++;
    }
  while(width > max_width);

  height *= lineCount;

  this->setFixedSize(QSize(width, height));

  update();
}


