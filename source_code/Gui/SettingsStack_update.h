#ifndef GUISETTINGSSTACK_UPDATE_H
#define GUISETTINGSSTACK_UPDATE_H

#include "Gui/Frameworks/ScrollStack.h"
#include <QCheckBox>
#include <QPushButton>

class GuiSettingsStack_update : public ScrollStack
{
  Q_OBJECT
public:
  explicit GuiSettingsStack_update(QWidget *parent = 0);

private:
  QLabel *update_available_label;
  QBoxLayout *update_available_layout;
};

#endif // GUISETTINGSSTACK_UPDATE_H
