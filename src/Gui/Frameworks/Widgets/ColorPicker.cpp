#include "ColorPicker.h"
#include "Global.h"

ColorPicker::ColorPicker(QColor *color, QWidget *parent)
  : QWidget(parent)
  , rectangle(QRect(1, 1, 18, 18))
  , result_color(color)
{
  this->setFixedSize(20,20);
}

ColorPicker::~ColorPicker()
{

}

QColor ColorPicker::color()
{
  return *result_color;
}

void ColorPicker::paintEvent(QPaintEvent *)
{
  QPainter paint;
  paint.begin(this);
  paint.setPen(result_color->darker(120));
  paint.setBrush(QBrush(*result_color,Qt::SolidPattern));
  paint.setRenderHint(QPainter::Antialiasing,true);
  paint.drawRoundedRect(rectangle,5,5);
  paint.end();
}

void ColorPicker::mouseReleaseEvent(QMouseEvent *ev)
{
  if (ev->button() == Qt::LeftButton)
    {
      QColor color = QColorDialog::getColor(*result_color, this);
      if(!color.isValid()
         || color == QColor(0,0,0)
         || color == QColor(255,255,255))
        {
          return;
        }

      *result_color = color;
      Global::settings.modified = true;
      repaint();
    }
}

