#ifndef GUIWELCOMESTACK_H
#define GUIWELCOMESTACK_H

#include "Gui/Frameworks/Widgets/LabelButton.h"
#include "Gui/Frameworks/Widgets/AvatarButton.h"
#include "GlobalData.h"

#include <QStackedLayout>
#include <QRadialGradient>
#include <QPainter>
#include <QTime>
#include <QDebug>

class GuiHomeStack_welcome : public QWidget
{
  Q_OBJECT

public:
  explicit GuiHomeStack_welcome(QWidget *parent = 0);

protected:
  void paintEvent(QPaintEvent *);

private:
  QHBoxLayout *bottom_layout;
  QVBoxLayout *profile_layout;

  QWidget *profile_widget;
  QLabel *usr_name_label;
  QLabel *welcome_label;
  QLabel *ip_label;
  QLabel *host_name_label;
  QLabel *background_label;

  GuiAvatarButton *my_avatar;

  QColor blur_color;

  int radial_radius = 60;
  int enlarge = true;
  bool online = false;

  void refreshCenter();

private slots:
  void refreshUI();
};

#endif // GUIWELCOMESTACK_H
