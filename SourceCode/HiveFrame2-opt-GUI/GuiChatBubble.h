#ifndef GUICHATBUBBLE_H
#define GUICHATBUBBLE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPixmap>

#include <QLabel>
#include <QPainter>
#include <QRect>
#include <QHBoxLayout>
#include <QDebug>

class GuiChatBubble_text_area : public QLabel
{
public:
  explicit GuiChatBubble_text_area(QString text, int maxWidth, bool alignLeft, QWidget *parent = 0);

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


class GuiChatBubble : public QWidget
{
  Q_OBJECT

public:
  explicit GuiChatBubble(QString text, bool alignLeft, QWidget *parent = 0);

private:
  QHBoxLayout *main_layout;
  QPixmap strip_pixmap;
  QLabel *strip;
  GuiChatBubble_text_area *text_area;


};

#endif // GUICHATBUBBLE_H
