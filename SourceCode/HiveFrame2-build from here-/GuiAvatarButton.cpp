#include "GuiAvatarButton.h"
#include <QDebug>

GuiAvatarButton::GuiAvatarButton(const QString path, const int Diameter, QWidget *parent)
{
  diameter = Diameter;
  setAvatar(path);

  this->setParent(parent);
}

GuiAvatarButton::GuiAvatarButton(const int Diameter, QWidget *parent)
{
  diameter = Diameter;
  this->setParent(parent);
}

void GuiAvatarButton::setAvatar(const QString &path)
{
  QBitmap mask(QSize(diameter,diameter));
  QPainter painter(&mask);
  painter.setRenderHint(QPainter::Antialiasing);
  painter.setRenderHint(QPainter::SmoothPixmapTransform);
  painter.fillRect(0, 0, diameter, diameter, Qt::white);
  painter.setBrush(Qt::black);
  painter.drawRoundedRect(0, 0, diameter, diameter, 99, 99);


  QPixmap avatar_pixmap(path);
  avatar_pixmap = avatar_pixmap.scaled(diameter,diameter,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);

  avatar_pixmap.setDevicePixelRatio(2.0);
  avatar_pixmap.setMask(mask);

  this->setPixmap(avatar_pixmap);
}


////////////events

void GuiAvatarButton::mouseReleaseEvent(QMouseEvent *ev)
{
  if (ev->button() == Qt::LeftButton)
  emit clicked();
}

void GuiAvatarButton::enterEvent(QEvent *)
{
  //setState1();
  //emit entered();
}

void GuiAvatarButton::leaveEvent(QEvent *)
{
  //setState0();
  //emit left();
}


/*
void getRoundPixmap(QPixmap& src,QSize size)

{

  QImage resultImage(size,QImage::Format_ARGB32_Premultiplied);

  QPixmap head_mask("mask.png");

  QPainter painter(&resultImage);

  painter.setCompositionMode(QPainter::CompositionMode_Source);

  painter.fillRect(resultImage.rect(), Qt::transparent);

  painter.setCompositionMode(QPainter::CompositionMode_SourceOver);

  painter.drawPixmap(0, 0, head_mask);

  painter.setCompositionMode(QPainter::CompositionMode_SourceOut);

  painter.drawPixmap(0, 0, src.scaled(size));

  painter.setCompositionMode(QPainter::CompositionMode_DestinationOver);

  painter.end();



  src = QPixmap::fromImage(resultImage);

}
*/
