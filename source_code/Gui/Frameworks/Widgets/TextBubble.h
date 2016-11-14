#ifndef GUICHATBUBBLE_H
#define GUICHATBUBBLE_H

#include "GlobalData.h"
#include <QLabel>
#include <QPainter>
#include <QHBoxLayout>

class TextBubble_text_area;
class TextBubble;

class GuiFileBubble_file_info;
class GuiFileBubble;

class TextBubble_text_area : public QLabel
{
  Q_OBJECT

public:
  explicit TextBubble_text_area(const QString &text, bool alignLeft, QWidget *parent = 0);

protected:
  void paintEvent(QPaintEvent *);

private:
  QHBoxLayout *main_layout;
  QLabel *label;
  QColor *color;

};


class TextBubble : public QWidget
{
  Q_OBJECT

public:
  explicit TextBubble(const QString &text, bool alignLeft, QWidget *parent = 0);
  TextBubble_text_area *text_area;


private:
  QHBoxLayout *main_layout;
  QPixmap strip_pixmap;
  QLabel *strip;////this hurts my heart!
};


class GuiFileBubble_file_info : public QLabel
{
  Q_OBJECT

public:
  explicit GuiFileBubble_file_info(const QString &text, bool alignLeft, QWidget *parent = 0);

protected:
  void paintEvent(QPaintEvent *);

private:
  QHBoxLayout *main_layout;

  QLabel *label;
  QColor *color;

};

class GuiFileBubble : public QWidget
{
  Q_OBJECT

public:
  explicit GuiFileBubble(const QString &text, bool alignLeft, QWidget *parent = 0);
  GuiFileBubble_file_info *file_info;


private:
  QHBoxLayout *main_layout;
  QPixmap strip_pixmap;
  QLabel *strip;////this hurts my heart!
};

#endif // GUICHATBUBBLE_H
