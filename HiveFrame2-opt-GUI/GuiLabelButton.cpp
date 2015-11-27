#include "GuiLabelButton.h"

GuiLabelButton::GuiLabelButton(QWidget *parent)
{
  this->setParent(parent);
}

void GuiLabelButton::setState0Pixmap(QString path)
{
  state0_pixmap.load(path);
  state0_pixmap.setDevicePixelRatio(2.0);
  this->setPixmap(state0_pixmap);
}

void GuiLabelButton::setState1Pixmap(QString path)
{
  state1_pixmap.load(path);
  state1_pixmap.setDevicePixelRatio(2.0);
}

void GuiLabelButton::setState0()
{
  this->setPixmap(state0_pixmap);
}

void GuiLabelButton::setState1()
{
  this->setPixmap(state1_pixmap);
}


////////////events

void GuiLabelButton::mouseReleaseEvent(QMouseEvent *ev)
{
  if (ev->button() == Qt::LeftButton)
  emit clicked();
}

void GuiLabelButton::enterEvent(QEvent * )
{
  setState1();
  emit entered();
}

void GuiLabelButton::leaveEvent(QEvent *)
{
  setState0();
  emit left();
}
