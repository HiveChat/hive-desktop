#ifndef GUICHATBUBBLE_H
#define GUICHATBUBBLE_H

#include "Global.h"
#include <QLabel>
#include <QPainter>
#include <QHBoxLayout>

class TextBubble_text_area;
class TextBubble;

class FileBubble_file_info;
class FileBubble;

class TextBubble_text_area : public QWidget
{
  Q_OBJECT

public:
  explicit TextBubble_text_area(const QString &text, const bool alignLeft, QWidget *parent = nullptr);

protected:
  void paintEvent(QPaintEvent *);

private:
  QString message;
  QHBoxLayout *main_layout;
  QLabel *label;
  QColor *color;

};


class TextBubble : public QWidget
{
  Q_OBJECT

public:
  explicit TextBubble(const QString &text, bool alignLeft, QWidget *parent = nullptr);
  TextBubble_text_area *text_area;

private:
  QHBoxLayout *main_layout;
  QPixmap strip_pixmap;
  QLabel *strip;////this hurts my heart!
};


class FileBubble_file_info : public QLabel
{
  Q_OBJECT

public:
  explicit FileBubble_file_info(const QString &text, bool alignLeft, QWidget *parent = nullptr);

protected:
  void paintEvent(QPaintEvent *);

private:
  QHBoxLayout *main_layout;

  QLabel *label;
  QColor *color;

};

class FileBubble : public QWidget
{
  Q_OBJECT

public:
  explicit FileBubble(const QString &text, bool alignLeft, QWidget *parent = nullptr);
  FileBubble_file_info *file_info;


private:
  QHBoxLayout *main_layout;
  QPixmap strip_pixmap;
  QLabel *strip;////this hurts my heart!
};

#endif // GUICHATBUBBLE_H
