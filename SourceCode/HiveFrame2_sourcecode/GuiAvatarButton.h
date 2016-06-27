#ifndef GUIAVATARBUTTON_H
#define GUIAVATARBUTTON_H

#include <QLabel>
#include <QMouseEvent>
#include <QPixmap>
#include <QPainter>
#include <QBitmap>


class GuiAvatarButton : public QLabel
{
  Q_OBJECT

public:
  GuiAvatarButton(const QString path, const int Diameter, QWidget *parent);
  GuiAvatarButton(const int Diameter, QWidget *parent);

  void setAvatar(const QString &path);

protected:
  void mouseReleaseEvent(QMouseEvent *);
  void enterEvent(QEvent *);
  void leaveEvent(QEvent *);

private:
  int diameter;

signals:
  void clicked();


};

#endif // GUIAVATARBUTTON_H
