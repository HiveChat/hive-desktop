#ifndef GuiLabelButton_H
#define GuiLabelButton_H

#include <QLabel>
#include <QMouseEvent>
#include <QTimer>
#include <QDebug>

class LabelButton : public QLabel
{
  Q_OBJECT

public:
  explicit LabelButton(const int &hoverDelay = 0, QWidget *parent = 0);

  void setDefaultPixmap(const QString &path);
  void setHoveredPixmap(const QString &path);
  void setPressedPixmap(const QString &path);
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

  int hover_delay;
  bool hover_signal_lock;

};

#endif // GuiLabelButton_H
