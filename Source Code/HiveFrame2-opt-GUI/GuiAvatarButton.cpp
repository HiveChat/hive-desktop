#include "GuiAvatarButton.h"

GuiAvatarButton::GuiAvatarButton(QString path, const int Diameter, int borderWidth, QWidget *parent)
{
  diameter = Diameter;
  border_width = borderWidth;

  QBitmap mask(QSize(Diameter,Diameter));
  QPainter painter(&mask);
  painter.setRenderHint(QPainter::Antialiasing);
  painter.setRenderHint(QPainter::SmoothPixmapTransform);
  painter.fillRect(0, 0, Diameter, Diameter, Qt::white);
  painter.setBrush(QColor(0, 0, 0));
  painter.drawRoundedRect(0, 0, Diameter, Diameter, 99, 99);

  QPixmap avatar_pixmap(path);
  avatar_pixmap = avatar_pixmap.scaled(Diameter,Diameter,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);

  avatar_pixmap.setDevicePixelRatio(2.0);
  avatar_pixmap.setMask(mask);

  this->setPixmap(avatar_pixmap);
  this->setParent(parent);
}


////////////events

void GuiAvatarButton::mouseReleaseEvent(QMouseEvent *ev)
{
  if (ev->button() == Qt::LeftButton);
  //emit clicked();
}

void GuiAvatarButton::enterEvent(QEvent * )
{
  //setState1();
  //emit entered();
}

void GuiAvatarButton::leaveEvent(QEvent *)
{
  //setState0();
  //emit left();
}
