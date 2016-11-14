#include "LabelButton.h"

/*
 * Try to use:
 *  qreal dpr = App::app()->devicePixelRatio();
 * To get suitable pixel ratio in different devices
 *
 */


LabelButton::LabelButton(QWidget *parent)
{
  this->setParent(parent);
}

void LabelButton::setDefaultPixmap(QString path)
{

  default_pixmap.load(path);
  default_pixmap.setDevicePixelRatio(2.0);
  this->setPixmap(default_pixmap);
}

void LabelButton::setHoveredPixmap(QString path)
{
  hovered_pixmap.load(path);
  hovered_pixmap.setDevicePixelRatio(2.0);
}

void LabelButton::setPressedPixmap(QString path)
{
  pressed_pixmap.load(path);
  pressed_pixmap.setDevicePixelRatio(2.0);
}

void LabelButton::setDefault()
{
  this->setPixmap(default_pixmap);
}

void LabelButton::setHovered()
{
  this->setPixmap(hovered_pixmap);
}


////////////events
void LabelButton::mousePressEvent(QMouseEvent *ev)
{
  if (ev->button() == Qt::LeftButton)
    {
      if(!pressed_pixmap.isNull())
        {
          this->setPixmap(pressed_pixmap);
        }
    }

}

void LabelButton::mouseReleaseEvent(QMouseEvent *ev)
{
  if (ev->button() == Qt::LeftButton)
    {
      //this->setPixmap(default_pixmap);
      emit clicked();
    }
}

void LabelButton::enterEvent(QEvent * )
{
  setHovered();
  emit entered();
}

void LabelButton::leaveEvent(QEvent *)
{
  setDefault();
  emit left();
}
