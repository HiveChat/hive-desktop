#include "GuiColorPicker.h"
#include <QDebug>
#include <GlobalData.h>

GuiColorPicker::GuiColorPicker(QColor *color, QWidget *parent) : QWidget(parent)
{
  this->setFixedSize(20,20);
  my_color = color;
}

GuiColorPicker::~GuiColorPicker()
{

}

QColor GuiColorPicker::color()
{
  return *my_color;
}

void GuiColorPicker::paintEvent(QPaintEvent *)
{
  QRectF rectangle(1, 1, 18, 18);
  QPainter paint;

  paint.begin(this);
  paint.setPen(QColor(my_color->red()*0.8,my_color->green()*0.8,my_color->blue()*0.8));
  paint.setBrush(QBrush(*my_color,Qt::SolidPattern));
  paint.setRenderHint(QPainter::Antialiasing,true);
  paint.drawRoundedRect(rectangle,5,5);
  paint.end();
}

void GuiColorPicker::mouseReleaseEvent(QMouseEvent *ev)
{
  if (ev->button() == Qt::LeftButton)
    {
      *my_color = QColorDialog::getColor(Qt::white, this);
      repaint();
      emit clicked();
    }
}

