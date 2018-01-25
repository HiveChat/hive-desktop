#ifndef GUISETTINGSSTACK_UPDATE_H
#define GUISETTINGSSTACK_UPDATE_H

#include "Gui/Frameworks/ScrollStack.h"
#include <QCheckBox>
#include <QPushButton>

class SettingsStack_update : public ScrollStack
{
  Q_OBJECT
public:
  explicit SettingsStack_update(QWidget *parent = 0);

private:
  QLabel *update_available_label;
  QBoxLayout *update_available_layout;
};

#endif // GUISETTINGSSTACK_UPDATE_H
