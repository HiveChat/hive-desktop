#ifndef GUISETTINGSSTACK_MESSAGING_H
#define GUISETTINGSSTACK_MESSAGING_H

#include "GuiScrollStack.h"
#include "GuiColorPicker.h"
#include "GlobalData.h"

class GuiSettingsStack_messaging : public GuiScrollStack
{
  Q_OBJECT

public:
  explicit GuiSettingsStack_messaging(QWidget *parent = 0);
  ~GuiSettingsStack_messaging();

};

#endif // GUISETTINGSSTACK_MESSAGING_H
