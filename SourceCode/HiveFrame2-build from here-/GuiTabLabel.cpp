#include "GuiTabLabel.h"

GuiTabLabel::GuiTabLabel(QWidget *parent)
{
  palette.setColor(QPalette::WindowText, text_color);
  this->setPalette(palette);

  this->setParent(parent);

}

GuiTabLabel::GuiTabLabel(const QString &text)
{
  palette.setColor(QPalette::WindowText, text_color);
  this->setPalette(palette);

  QFont font;
  font.setPixelSize(font_pixel_size);
  this->setFont(font);

  this->setText(text);
}

void GuiTabLabel::setFontPixelSize(int size)
{
  font_pixel_size = size;
  QFont font;
  font.setPixelSize(font_pixel_size);
  this->setFont(font);
}

void GuiTabLabel::setTextColor(QColor color)
{
  text_color = color;
  this->setPalette(palette);
}

void GuiTabLabel::setHoveredTextColor(QColor color)
{
  hovered_text_color = color;
  this->setPalette(palette);
}

void GuiTabLabel::mouseReleaseEvent(QMouseEvent *ev)
{
  if (ev->button() == Qt::LeftButton)
  emit clicked();//(this);
}

void GuiTabLabel::enterEvent(QEvent * )
{
  palette.setColor(QPalette::WindowText, hovered_text_color);
  this->setPalette(palette);

  emit entered();
}

void GuiTabLabel::leaveEvent(QEvent *)
{
  palette.setColor(QPalette::WindowText, text_color);
  this->setPalette(palette);

  emit left();
}
