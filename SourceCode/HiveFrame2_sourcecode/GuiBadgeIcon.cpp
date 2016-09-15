#include "GuiBadgeIcon.h"

GuiBadgeIcon::GuiBadgeIcon(const int &dia, QWidget *parent) : QWidget(parent)
{
  height = dia;
  num_label = new QLabel(this);
  QPalette label_palette;
  label_palette.setColor(QPalette::WindowText, QColor(255, 255, 255));
  num_label->setPalette(label_palette);
  QFont label_font = num_label->font();
  label_font.setPointSize(8);
  num_label->setFont(label_font);
  num_label->setFrameRect(QRect(20, 12, height, height));
}

void GuiBadgeIcon::setNumber(const int &number)
{
  if(number == 0)
    {
      num_label->setHidden(true);
    }
  if(number < 10)
    {
      num_label->setFrameRect(QRect(22, 12, height, height));
      num_label->setText(QString::number(number));
      num_label->setHidden(false);
      return;
    }
  if(number > 99)
    {
      num_label->setFrameRect(QRect(20, 12, height, height));
      num_label->setText("...");
      num_label->setHidden(false);
      return;
    }
  else
    {
      num_label->setFrameRect(QRect(20, 12, height, height));
      num_label->setText(QString::number(number));
      num_label->setHidden(false);
      return;
    }
}

void GuiBadgeIcon::paintEvent(QPaintEvent *)
{
  QRectF rectangle(18, 10, height, height);
  QPainter paint;
  paint.begin(this);
  paint.setPen(color);
  paint.setBrush(QBrush(color, Qt::SolidPattern));
  paint.setRenderHint(QPainter::Antialiasing,true);
  paint.drawRoundedRect(rectangle, 7, 7);
  paint.end();
}
