#ifndef GUITABLABEL_H
#define GUITABLABEL_H

#include <QLabel>
#include <QMouseEvent>

class GuiTabLabel : public QLabel
{
  Q_OBJECT

 public:
     explicit GuiTabLabel(QWidget *parent = 0);
     GuiTabLabel(const QString &text);
 signals:
     void clicked();//IMClickLabel* label);

 protected:
     // 鼠标单击事件
     void mouseReleaseEvent(QMouseEvent *);
     //void enterEvent(QEvent *);
     //void leaveEvent(QEvent *);
 public slots:
};

#endif // GUITABLABEL_H
