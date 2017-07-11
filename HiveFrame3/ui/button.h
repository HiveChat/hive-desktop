#ifndef BUTTON_H
#define BUTTON_H

#include <QOpenGLWidget>
#include <QPainter>
#include <QStaticText>
#include <QFontMetrics>
#include <QDebug>

class Button : public QOpenGLWidget
{
  Q_OBJECT
public:
  explicit Button(const QString &txt, int w = 0, int h = 100, QWidget *parent = 0);
  explicit Button(const QString &txt, QWidget *parent = 0);

  void setFont(const QFont &font);
  void setFont(const QString &family, const int &pixelSize);
  void setText(const QString &str);


protected:
  void paintEvent(QPaintEvent *);
  void mousePressEvent(QMouseEvent *);
  void mouseReleaseEvent(QMouseEvent *);
  void enterEvent(QEvent *);
  void leaveEvent(QEvent *);

private:
  bool hovered = false;

  int width;
  int height = 30;

  QString text;
  QFont font;

  QColor background_default_color = Qt::white;
  QColor background_hovered_color = QColor(245,245,245);
  QColor foreground_default_color = QColor(180,180,180);
  QColor foreground_hovered_color = QColor(140,140,140);


  void updateTextRect();




signals:
  void clicked();
};

#endif // BUTTON_H
