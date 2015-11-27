#ifndef GuiLabelButton_H
#define GuiLabelButton_H

#include <QLabel>
#include <QMouseEvent>

class GuiLabelButton : public QLabel
{
  Q_OBJECT

 public:
     explicit GuiLabelButton(QWidget *parent = 0);

     void setState0Pixmap(QString path);
     void setState1Pixmap(QString path);

     void setState0();
     void setState1();

 signals:
     void clicked();
     void entered();
     void left();

 protected:
     void mouseReleaseEvent(QMouseEvent *);
     void enterEvent(QEvent *);
     void leaveEvent(QEvent *);

private:
     QPixmap state0_pixmap;
     QPixmap state1_pixmap;

};

#endif // GuiLabelButton_H
