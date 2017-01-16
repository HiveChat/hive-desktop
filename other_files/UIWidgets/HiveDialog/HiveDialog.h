#ifndef WIDGET_H
#define WIDGET_H

#include "GuiLabelButton.h"

#include <QWidget>
#include <QHBoxLayout>
#include <QPainter>
//#include <QBitmap>

class HiveDialog : public QWidget
{
  Q_OBJECT

public:
  HiveDialog(QString title, QString content, QSize size = QSize(450,200), QWidget *parent = 0);
  ~HiveDialog();


protected:
  void paintEvent(QPaintEvent*);

  void mousePressEvent(QMouseEvent *event);
  void mouseReleaseEvent(QMouseEvent *event);
  void mouseMoveEvent(QMouseEvent *event);

private:

  QHBoxLayout *window_btn_layout;

  GuiLabelButton *exit_hint;
  GuiLabelButton *min_hint;
  GuiLabelButton *max_hint;

  QPoint move_point;
  bool maximized = false;
  bool mouse_pressed;


private slots:
  void changeWindowBtn();
  void recoverWindowBtn();

  void setWindowMaximized();


};

#endif // WIDGET_H
