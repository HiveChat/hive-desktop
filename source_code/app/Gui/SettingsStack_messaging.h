#ifndef GUISETTINGSSTACK_MESSAGING_H
#define GUISETTINGSSTACK_MESSAGING_H

#include "Gui/Frameworks/ScrollStack.h"
#include "Gui/Frameworks/Widgets/ColorPicker.h"
#include <QPushButton>
#include <QCheckBox>
#include <QDir>

class SettingsStack_messaging : public ScrollStack
{
  Q_OBJECT

public:
  explicit SettingsStack_messaging(QWidget *parent = 0);
  ~SettingsStack_messaging();

private:
  ColorPicker *in_bubble_picker;
  ColorPicker *out_bubble_picker;

  QPushButton *clear_btn;
  int make_sure = 0;

};

#endif // GUISETTINGSSTACK_MESSAGING_H
