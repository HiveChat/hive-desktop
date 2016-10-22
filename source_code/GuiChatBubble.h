#ifndef GUICHATBUBBLE_H
#define GUICHATBUBBLE_H

#include "GlobalData.h"
#include <QLabel>
#include <QPainter>
#include <QHBoxLayout>

class GuiChatBubble_text_area;
class GuiChatBubble;

class GuiFileBubble_file_info;
class GuiFileBubble;

class GuiChatBubble_text_area : public QLabel
{
  Q_OBJECT

public:
  explicit GuiChatBubble_text_area(const QString &text, bool alignLeft, QWidget *parent = 0);

protected:
  void paintEvent(QPaintEvent *);

private:
  QHBoxLayout *main_layout;
  QLabel *label;
  QColor *color;

};


class GuiChatBubble : public QWidget
{
  Q_OBJECT

public:
  explicit GuiChatBubble(const QString &text, bool alignLeft, QWidget *parent = 0);
  GuiChatBubble_text_area *text_area;


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
