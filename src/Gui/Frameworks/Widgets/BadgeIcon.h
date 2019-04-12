#ifndef GUIBADGEICON_H
#define GUIBADGEICON_H

#include <QWidget>
#include <QPainter>


class BadgeIcon : public QWidget
{
  Q_OBJECT
public:
  explicit BadgeIcon(const int &dia, QWidget *parent = nullptr);

  void setNumber(const int &number);

protected:
  void paintEvent(QPaintEvent*);

private:
  int number;
  int height;
  QRectF rectangle;
  QColor color = QColor(237,64,64);
};

#endif // GUIBADGEICON_H
