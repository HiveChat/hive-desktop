#ifndef GUIBADGEICON_H
#define GUIBADGEICON_H

#include <QLabel>
#include <QPainter>


class GuiBadgeIcon : public QWidget
{
  Q_OBJECT
public:
  explicit GuiBadgeIcon(const int &dia,QWidget *parent = 0);

  void setNumber(const int &number);

protected:
  void paintEvent(QPaintEvent*);

private:
  int number;
  int height;
  QColor color = QColor("#D31111");

  QLabel *num_label;

};

#endif // GUIBADGEICON_H
