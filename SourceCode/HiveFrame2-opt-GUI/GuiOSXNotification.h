#ifndef GUIOSXNOTIFICATION_H
#define GUIOSXNOTIFICATION_H

#include <QWidget>
#include <QDesktopWidget>
#include <QPropertyAnimation>
#include <QPoint>
#include <QTimer>
#include <QPainter>
#include <QPen>

class GuiOSXNotification : public QWidget
{
  Q_OBJECT

public:
  explicit GuiOSXNotification(QWidget *parent = 0);
  ~GuiOSXNotification();

protected:
  void paintEvent(QPaintEvent*);

private:
  QPoint startPoint;
  QPoint endPoint;

  QDesktopWidget desktop;
  QPropertyAnimation* animation;
  QTimer *remainTimer;

  void showAnimation();
private slots:
  void closeAnimation();
  void clearAll();
};


#endif // GUIOSXNOTIFICATION_H
