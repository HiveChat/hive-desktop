#ifndef GUIBUTTON_H
#define GUIBUTTON_H

#include <QLabel>
#include <QPainter>
#include <QRect>
#include <QHBoxLayout>
#include <QDebug>

class GuiButton : public QLabel
{
public:
  explicit GuiButton(QString text, int maxWidth, QWidget *parent = 0);

protected:
  void paintEvent(QPaintEvent *);

private:
  QHBoxLayout *main_layout;

  QPixmap background_pixmap;
  QLabel *label;
  QRect mrect;

  int rect_width;
  int rect_height;

};

#endif // GUIBUTTON_H
