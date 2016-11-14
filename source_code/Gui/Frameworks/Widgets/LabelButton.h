#ifndef GuiLabelButton_H
#define GuiLabelButton_H

#include <QLabel>
#include <QMouseEvent>

class LabelButton : public QLabel
{
  Q_OBJECT

public:
  explicit LabelButton(QWidget *parent = 0);

  void setDefaultPixmap(QString path);
  void setHoveredPixmap(QString path);
  void setPressedPixmap(QString path);

  void setDefault();
  void setHovered();

signals:
  void clicked();
  void entered();
  void left();

protected:
  void mousePressEvent(QMouseEvent *);
  void mouseReleaseEvent(QMouseEvent *);
  void enterEvent(QEvent *);
  void leaveEvent(QEvent *);

private:
  QPixmap default_pixmap;
  QPixmap hovered_pixmap;
  QPixmap pressed_pixmap;

};

#endif // GuiLabelButton_H
