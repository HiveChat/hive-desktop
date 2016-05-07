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

     void setFontPixelSize(int size);
     void setBaseColor(QColor color);
     void setTextColor(QColor color);
     void setHoveredTextColor(QColor color);

 signals:
     void clicked();//IMClickLabel* label);
     void entered();
     void left();

 protected:
     // 鼠标单击事件
     void mouseReleaseEvent(QMouseEvent *);
     void enterEvent(QEvent *);
     void leaveEvent(QEvent *);

 public slots:

private:
     QPalette palette;
     int font_pixel_size = 18;
     QColor text_color = QColor(106,74,0,255);
     QColor hovered_text_color = QColor(255,255,255,255);

};

#endif // GUITABLABEL_H
