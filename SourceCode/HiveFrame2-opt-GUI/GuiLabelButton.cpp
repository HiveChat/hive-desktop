#include "GuiLabelButton.h"

/*
 * Try to use:
 *  qreal dpr = App::app()->devicePixelRatio();
 * To get suitable pixel ratio in different devices
 *
 */


GuiLabelButton::GuiLabelButton(QWidget *parent)
{
  this->setParent(parent);
}

void GuiLabelButton::setDefaultPixmap(QString path)
{

  default_pixmap.load(path);
  default_pixmap.setDevicePixelRatio(2.0);
  this->setPixmap(default_pixmap);
}

void GuiLabelButton::setHoveredPixmap(QString path)
{
  hovered_pixmap.load(path);
  hovered_pixmap.setDevicePixelRatio(2.0);
}

void GuiLabelButton::setPressedPixmap(QString path)
{
  pressed_pixmap.load(path);
  pressed_pixmap.setDevicePixelRatio(2.0);
}

void GuiLabelButton::setDefault()
{
  this->setPixmap(default_pixmap);
}

void GuiLabelButton::setHovered()
{
  this->setPixmap(hovered_pixmap);
}


////////////events
void GuiLabelButton::mousePressEvent(QMouseEvent *ev)
{
  if (ev->button() == Qt::LeftButton)
    {
      if(!pressed_pixmap.isNull())
        {
          this->setPixmap(pressed_pixmap);
        }
    }

}

void GuiLabelButton::mouseReleaseEvent(QMouseEvent *ev)
{
  if (ev->button() == Qt::LeftButton)
    {
      //this->setPixmap(default_pixmap);
      emit clicked();
    }
}

void GuiLabelButton::enterEvent(QEvent * )
{
  setHovered();
  emit entered();
}

void GuiLabelButton::leaveEvent(QEvent *)
{
  setDefault();
  emit left();
}
