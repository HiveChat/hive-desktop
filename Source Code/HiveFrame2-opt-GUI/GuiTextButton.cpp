#include "GuiTextButton.h"

GuiTextButton::GuiTextButton(QWidget *parent)
{
  palette.setColor(QPalette::WindowText, text_color);
  this->setPalette(palette);

  this->setParent(parent);

}

GuiTextButton::GuiTextButton(const QString &text)
{
  palette.setColor(QPalette::WindowText, text_color);
  this->setPalette(palette);

  QFont font;
  font.setPixelSize(font_pixel_size);
  this->setFont(font);

  this->setText(text);
}

void GuiTextButton::setFontPixelSize(int size)
{
  font_pixel_size = size;
  QFont font;
  font.setPixelSize(font_pixel_size);
  this->setFont(font);
}

void GuiTextButton::setState0TextColor(QColor color)
{
  text_color = color;
  this->setPalette(palette);
}

void GuiTextButton::setState1TextColor(QColor color)
{
  hovered_text_color = color;
  this->setPalette(palette);
}

////////////events

void GuiTextButton::mouseReleaseEvent(QMouseEvent *ev)
{
  if (ev->button() == Qt::LeftButton)
  emit clicked();
}

void GuiTextButton::enterEvent(QEvent * )
{
  palette.setColor(QPalette::WindowText,hovered_text_color);
  this->setPalette(palette);

  emit entered();
}

void GuiTextButton::leaveEvent(QEvent *)
{
  palette.setColor(QPalette::WindowText, text_color);
  this->setPalette(palette);

  emit left();
}

