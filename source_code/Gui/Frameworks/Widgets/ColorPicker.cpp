#include "ColorPicker.h"
#include "GlobalData.h"

GuiColorPicker::GuiColorPicker(QColor *color, QWidget *parent)
  : QWidget(parent)
  , my_color(color)
  , rectangle(QRect(1, 1, 18, 18))
{
  this->setFixedSize(20,20);
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
  QPainter paint;
  paint.begin(this);
  paint.setPen(/*QColor(my_color->red()*0.8,my_color->green()*0.8,my_color->blue()*0.8)*/my_color->darker(120));
  paint.setBrush(QBrush(*my_color,Qt::SolidPattern));
  paint.setRenderHint(QPainter::Antialiasing,true);
  paint.drawRoundedRect(rectangle,5,5);
  paint.end();
}

void GuiColorPicker::mouseReleaseEvent(QMouseEvent *ev)
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
      GlobalData::settings_struct.modified_lock = true;
      repaint();
    }
}

