#include "LabelButton.h"

/*
 * Try to use:
 *  qreal dpr = App::app()->devicePixelRatio();
 * To get suitable pixel ratio in different devices
 *
 */

LabelButton::LabelButton(const int &hoverDelay, QWidget *parent)
  : QLabel(parent)
  , hover_delay(hoverDelay)
{
}

void LabelButton::setDefaultPixmap(const QString &path)
{
  default_pixmap.load(path);
  default_pixmap.setDevicePixelRatio(Global::window_dpr);
  this->setPixmap(default_pixmap);
}

void LabelButton::setHoveredPixmap(const QString &path)
{
  hovered_pixmap.load(path);
  hovered_pixmap.setDevicePixelRatio(Global::window_dpr);
}

void LabelButton::setPressedPixmap(const QString &path)
{
  pressed_pixmap.load(path);
  pressed_pixmap.setDevicePixelRatio(Global::window_dpr);
}

void LabelButton::setDefault()
{
  if(!disabled)
    {
      this->setPixmap(default_pixmap);
    }
}

void LabelButton::setHovered()
{
  if(!disabled)
    {
      this->setPixmap(hovered_pixmap);
    }
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
  if(hover_delay != 0)
    {
      hover_signal_lock = false;
      QTimer::singleShot(hover_delay, [this]() {
          if(!hover_signal_lock)
            {
              emit entered();
            }
          else
            {
              hover_signal_lock = false;
            }
        });
    }
  else
    {
      emit entered();
    }
}

void LabelButton::leaveEvent(QEvent *)
{
  setDefault();
  if(hover_delay != 0)
    {
      if(!hover_signal_lock)
        {
          emit left();
          hover_signal_lock = true;
        }
    }
  else
    {
      emit left();
    }
}



