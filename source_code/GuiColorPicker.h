#ifndef GUICOLORPICKER_H
#define GUICOLORPICKER_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QColorDialog>
#include "GlobalData.h"

class GuiColorPicker : public QWidget
{
  Q_OBJECT

public:
  explicit GuiColorPicker(QColor *object_color, QWidget *parent = 0);
  ~GuiColorPicker();

  QColor color();

protected:
  void paintEvent(QPaintEvent*);
  void mouseReleaseEvent(QMouseEvent *);

private:
  QColor *my_color;

};

#endif // GUICOLORPICKER_H
