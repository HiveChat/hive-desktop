#ifndef GUICHATBUBBLE_H
#define GUICHATBUBBLE_H

#include "GlobalData.h"

#include <QLabel>
#include <QPainter>
#include <QHBoxLayout>
#include <QMouseEvent>

class GuiChatBubble_text_area : public QLabel
{
  Q_OBJECT

public:
  explicit GuiChatBubble_text_area(QString text, int maxWidth, bool alignLeft, QWidget *parent = 0);

protected:
  void paintEvent(QPaintEvent *);
  void mouseReleaseEvent(QMouseEvent *);

private:
  QHBoxLayout *main_layout;

  QPixmap background_pixmap;
  QLabel *label;
  QRect mrect;

  int rect_width;
  int rect_height;

  QColor color;

signals:
  void clicked();

};


class GuiChatBubble : public QWidget
{
  Q_OBJECT

public:
  explicit GuiChatBubble(QString text, bool alignLeft, QWidget *parent = 0);
  GuiChatBubble_text_area *text_area;


private:
  QHBoxLayout *main_layout;
  QPixmap strip_pixmap;
  QLabel *strip;////this hurts my heart!
};

#endif // GUICHATBUBBLE_H
