#include "GuiColorPicker.h"

GuiColorPicker::GuiColorPicker(QColor color, QWidget *parent) : QWidget(parent)
{
  this->setFixedSize(20,20);
  my_color = color;
}

GuiColorPicker::~GuiColorPicker()
{

}

QColor GuiColorPicker::color()
{
  return my_color;
}

void GuiColorPicker::paintEvent(QPaintEvent *)
{
  QRectF rectangle(0, 0, this->width(), this->height());
  QPainter paint;
  paint.begin(this);
  paint.setPen(QPen(Qt::NoPen));
  paint.setBrush(QBrush(my_color,Qt::SolidPattern));
  paint.setRenderHint(QPainter::Antialiasing,true);
  paint.drawRoundedRect(rectangle,10,10);
  paint.end();
}

void GuiColorPicker::mouseReleaseEvent(QMouseEvent *ev)
{
  if (ev->button() == Qt::LeftButton)
    {
      my_color = QColorDialog::getColor(Qt::white, this);
      repaint();
      emit clicked();
    }
}

