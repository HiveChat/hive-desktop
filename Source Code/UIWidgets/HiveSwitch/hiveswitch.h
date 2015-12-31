#ifndef HIVESWITCH_H
#define HIVESWITCH_H

#include <QWidget>
#include <QLabel>
#include <QStateMachine>
#include <QPropertyAnimation>
#include <QPainter>
#include <QSignalTransition>

class HiveSwitch : public QWidget
{
  Q_OBJECT

public:
  HiveSwitch(QWidget *parent = 0);
  ~HiveSwitch();

protected:
  void paintEvent(QPaintEvent*);
  void mouseReleaseEvent(QMouseEvent *event);

private:
  QPixmap slot_pixmap;
  QPixmap switch_pixmap;

  QLabel *switch_label;

signals:
  void clicked();
};

#endif // HIVESWITCH_H
