#ifndef GUIWELCOMESTACK_H
#define GUIWELCOMESTACK_H

#include "GuiLabelButton.h"
#include "GuiAvatarButton.h"
#include "GlobalData.h"

#include <QStackedLayout>
#include <QTime>
#include <QDebug>

class GuiHomeStack_welcome : public QWidget
{
  Q_OBJECT

public:
  explicit GuiHomeStack_welcome(QWidget *parent = 0);
  void refreshUI();

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

  QPixmap icon_pixmap;
};

#endif // GUIWELCOMESTACK_H
