#ifndef GUICOLORPICKER_H
#define GUICOLORPICKER_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QColorDialog>

class GuiColorPicker : public QWidget
{
  Q_OBJECT

public:
  explicit GuiColorPicker(QColor *color, QWidget *parent = 0);
  ~GuiColorPicker();

  QColor color();

protected:
  void paintEvent(QPaintEvent*);
  void mouseReleaseEvent(QMouseEvent *);

private:
  QColor *my_color;

signals:
  void clicked();
};

#endif // GUICOLORPICKER_H
