#include "BadgeIcon.h"
#include <QDebug>

GuiBadgeIcon::GuiBadgeIcon(const int &dia, QWidget *parent)
  : QWidget(parent)
  , height(dia)
  , rectangle(QRect(18, 10, dia, dia))
{
  this->setHidden(true);
}

void GuiBadgeIcon::setNumber(const int &num)
{
  number = num;
}

void GuiBadgeIcon::paintEvent(QPaintEvent *)
{
  if(number == 0)
    {
      this->setHidden(true);
      return;
    }

  QPainter paint(this);
  paint.begin(this);
  paint.setPen(color);
  paint.setBrush(QBrush(color, Qt::SolidPattern));
  paint.setRenderHint(QPainter::Antialiasing,true);
  paint.drawRoundedRect(rectangle, 7, 7);

  QFont font = this->font();
  font.setPointSize(8);
  paint.setPen(QColor(255,255,255));
  paint.setFont(font);

  if(number < 10)
    {
      paint.drawText(QPoint(22, 20), QString::number(number));
      paint.end();
      this->setHidden(false);
      return;
    }
  else if(number > 99)
    {
      paint.drawText(QPoint(21, 18), "...");
      paint.end();
      this->setHidden(false);
      return;
    }
  else
    {
      paint.drawText(QPoint(20, 20), QString::number(number));
      paint.end();
      this->setHidden(false);
      return;
    }
  paint.end();
}
