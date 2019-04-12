#ifndef GuiLabelButton_H
#define GuiLabelButton_H

#include "Global.h"

#include <QTimer>
#include <QLabel>
#include <QTextOption>
#include <QMouseEvent>
#include <QDebug>

class LabelButton : public QLabel
{
  Q_OBJECT

public:
  explicit LabelButton(const int &hoverDelay = 0, QWidget *parent = nullptr);

  void setDefaultPixmap(const QString &path);
  void setHoveredPixmap(const QString &path);
  void setPressedPixmap(const QString &path);
  void setDefault();
  void setHovered();
  void setDisabled(const bool &dis) {disabled = dis;}

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
  int disabled = false;
  bool hover_signal_lock;

signals:
  void clicked();
  void entered();
  void left();
};



class FloatButton : public QFrame
{
  Q_OBJECT
public:
  explicit FloatButton(const QString &txt, QWidget *parent = nullptr, const QColor &color = Qt::gray);

protected:
  void paintEvent(QPaintEvent *);
  void mousePressEvent(QMouseEvent *);
  void mouseReleaseEvent(QMouseEvent *);
  void enterEvent(QEvent *);
  void leaveEvent(QEvent *);

private:
  int width_;
  int height_;
  int radius_ = 15;
  QString text_;
  QColor color_;
  QFont font_;
  QTextOption text_option_;

  bool hovered_ = false;

signals:
  void clicked();
};

#endif // GuiLabelButton_H
