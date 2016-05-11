#ifndef GUIWELCOMESTACK_H
#define GUIWELCOMESTACK_H

#include "GuiLabelButton.h"
#include "GuiAvatarButton.h"
#include "GlobalData.h"
#include "NetManager.h"

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QStackedLayout>
#include <QPixmap>
#include <QTime>

#include <QDebug>

class GuiHomeStack_welcome : public QWidget
{
  Q_OBJECT

public:
  explicit GuiHomeStack_welcome(QWidget *parent = 0);

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

public slots:
  void refresh();

};

#endif // GUIWELCOMESTACK_H
