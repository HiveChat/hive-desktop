#ifndef GUIWELCOMESTACK_H
#define GUIWELCOMESTACK_H

#include "Gui/Frameworks/Widgets/LabelButton.h"
#include "Gui/Frameworks/Widgets/AvatarWidgets.h"
#include "GlobalData.h"

#include <QStackedLayout>
#include <QRadialGradient>
#include <QPainter>
#include <QVariantAnimation>
#include <QTime>
#include <QDebug>


class HomeStack_welcome : public QWidget
{
  Q_OBJECT

public:
  explicit HomeStack_welcome(QWidget *parent = 0);

protected:
  void mouseReleaseEvent(QMouseEvent *);



private:
  QHBoxLayout *bottom_layout;
  QVBoxLayout *profile_layout;

  QWidget *profile_widget;
  QLabel *usr_name_label;
  QLabel *welcome_label;
  QLabel *ip_label;
  QLabel *host_name_label;
  QLabel *background_label;

  AvatarButton *my_avatar;

  QColor blur_color;

  int radial_radius = 60;
  int enlarge = true;
  bool online = false;

  void refreshCenter();

private slots:
  void refreshUI();
};

#endif // GUIWELCOMESTACK_H
