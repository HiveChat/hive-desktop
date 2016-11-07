#ifndef GUISETTINGSSTACK_UPDATE_H
#define GUISETTINGSSTACK_UPDATE_H

#include "GuiScrollStack.h"
#include <QCheckBox>

class GuiSettingsStack_update : public GuiScrollStack
{
  Q_OBJECT
public:
  explicit GuiSettingsStack_update(QWidget *parent = 0);

private:
  QLabel *update_available_label;
  QBoxLayout *update_available_layout;
};

#endif // GUISETTINGSSTACK_UPDATE_H
