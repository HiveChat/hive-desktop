#ifndef GUISETTINGSSTACK_MESSAGING_H
#define GUISETTINGSSTACK_MESSAGING_H

#include "GuiScrollStack.h"
#include "GuiColorPicker.h"
#include <QPushButton>
#include <QCheckBox>

class GuiSettingsStack_messaging : public GuiScrollStack
{
  Q_OBJECT

public:
  explicit GuiSettingsStack_messaging(QWidget *parent = 0);
  ~GuiSettingsStack_messaging();

private:
  GuiColorPicker *in_bubble_picker;
  GuiColorPicker *out_bubble_picker;

};

#endif // GUISETTINGSSTACK_MESSAGING_H
