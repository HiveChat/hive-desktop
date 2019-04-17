#ifndef GUICOLORPICKER_H
#define GUICOLORPICKER_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QColorDialog>
#include "Global.h"

class ColorPicker : public QWidget
{
  Q_OBJECT
public:
  explicit ColorPicker(QColor *color, QWidget *parent = nullptr);
  ~ColorPicker();

  QColor color();

protected:
  void paintEvent(QPaintEvent*);
  void mouseReleaseEvent(QMouseEvent *);

private:
  QRect rectangle;
  QColor *result_color;
};

#endif // GUICOLORPICKER_H
