#ifndef GUIBUTTON_H
#define GUIBUTTON_H

#include <QLabel>
#include <QPainter>
#include <QRect>
#include <QHBoxLayout>

class GuiButton : public QLabel
{
public:
  explicit GuiButton(QString text, int maximumWidth, QWidget *parent);
  
protected:
  void paintEvent(QPaintEvent *);
  
private:
  QHBoxLayout *main_layout;

  QPixmap background_pixmap;
  QLabel *label;
  QRect rect;

  int width;
  int height;

};

#endif // GUIBUTTON_H
