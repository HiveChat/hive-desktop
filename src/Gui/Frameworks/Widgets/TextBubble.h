#ifndef GUICHATBUBBLE_H
#define GUICHATBUBBLE_H

#include "Global.h"
#include <QLabel>
#include <QPainter>
#include <QHBoxLayout>

class TextBubble;
class FileBubble;

class TextBubble : public QLabel
{
  Q_OBJECT

public:
  explicit TextBubble(const QString &text, const bool alignLeft, QWidget *parent = nullptr);

protected:
  void paintEvent(QPaintEvent *);

private:
  QString message;
  QHBoxLayout *main_layout;
  QLabel *label;
  QColor *color;

};



class FileBubble : public QLabel
{
  Q_OBJECT

public:
  explicit FileBubble(const QString &text, bool alignLeft, QWidget *parent = nullptr);

protected:
  void paintEvent(QPaintEvent *);

private:
  QHBoxLayout *main_layout;

  QLabel *label;
  QColor *color;

};

#endif // GUICHATBUBBLE_H
