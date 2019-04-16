#ifndef GUICOMBWIDGET_H
#define GUICOMBWIDGET_H

#include <QVBoxLayout>
#include <QHostAddress>
#include <QDragMoveEvent>
#include <QMouseEvent>
#include <QDrag>
#include <QPropertyAnimation>
#include <QMimeData>

#include "GlobalType.h"
#include "Global.h"
#include "Gui/Frameworks/Widgets/Button.h"
#include "Gui/Frameworks/Widgets/AvatarWidgets.h"
#include "Gui/Frameworks/Widgets/BadgeIcon.h"

class CombWidget : public QWidget
{
  Q_OBJECT

public:
  explicit CombWidget(UsrProfile *p, QWidget *parent = nullptr);
  ~CombWidget();

  void setProfile(UsrProfile *usrProfile);
  void setBadgeNumber(const int &num);

protected:
  bool mousePressed = false;
  QMouseEvent *mouseEvent;

//  void paintEvent(QPaintEvent  *);
  void mouseReleaseEvent(QMouseEvent *);
  void mousePressEvent(QMouseEvent *event);
  void enterEvent(QEvent *);
  void leaveEvent(QEvent *);
  void dragMoveEvent(QDragMoveEvent *);

private:
  AvatarButton *avatar;
  QLabel *usr_name_label;
  QLabel *ip_addr_label;
  QLabel *status_label;
  BadgeIcon *badge_icon;
  QVBoxLayout *usr_info_layout;
  QHBoxLayout *net_status_layout;
  QHBoxLayout *main_layout;

  const QString online_dot = "<span style=\" color:#39c828;\">●</span>";
  const QString offline_dot = "<span style=\" color:#ed403f;\">●</span>";
  const QString unstable_dot = "<span style=\" color:#ffb500;\">●</span>";

  QPalette hover_palette;
  QColor default_window_color = Qt::transparent;
  QColor hovered_window_color = Global::color_comb_selection;

  UsrProfile usr_profile;
  QString getSubNetStr(const QString &ipAddr);

signals:
  void clicked(const QString &usrKey);

};

#endif // GUICOMBWIDGET_H
