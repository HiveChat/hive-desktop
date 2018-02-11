#include "ColorPicker.h"
#include "GlobalData.h"

ColorPicker::ColorPicker(QColor *color, QWidget *parent)
  : QWidget(parent)
  , my_color(color)
  , rectangle(QRect(1, 1, 18, 18))
{
  this->setFixedSize(20,20);
}

ColorPicker::~ColorPicker()
{

}

QColor ColorPicker::color()
{
  return *my_color;
}

void ColorPicker::paintEvent(QPaintEvent *)
{
  QPainter paint;
  paint.begin(this);
  paint.setPen(my_color->darker(120));
  paint.setBrush(QBrush(*my_color,Qt::SolidPattern));
  paint.setRenderHint(QPainter::Antialiasing,true);
  paint.drawRoundedRect(rectangle,5,5);
  paint.end();
}

void ColorPicker::mouseReleaseEvent(QMouseEvent *ev)
{
  if (ev->button() == Qt::LeftButton)
    {
      QColor color = QColorDialog::getColor(*my_color, this);
      if(!color.isValid()
         || color == QColor(0,0,0)
         || color == QColor(255,255,255))
        {
          return;
        }

      *my_color = color;
      Global::settings.modified_lock = true;
      repaint();
    }
}

