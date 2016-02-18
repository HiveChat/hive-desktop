#ifndef GUISETTINGSSTACK_PROFILE_H
#define GUISETTINGSSTACK_PROFILE_H

#include "GuiScrollStack.h"
#include "GuiColorPicker.h"
#include "GlobalData.h"



class GuiSettingsStack_profile : public GuiScrollStack
{
  Q_OBJECT

public:
  explicit GuiSettingsStack_profile(QWidget *parent = 0);
  ~GuiSettingsStack_profile();

signals:

public slots:
};

#endif // GUISETTINGSSTACK_PROFILE_H
