#ifndef GUISETTINGSSTACK_QUESTIONS_H
#define GUISETTINGSSTACK_QUESTIONS_H

#include "GuiScrollStack.h"
#include "GuiColorPicker.h"
#include "GlobalData.h"

class GuiSettingsStack_questions : public GuiScrollStack
{
  Q_OBJECT

public:
  explicit GuiSettingsStack_questions(QWidget *parent = 0);
  ~GuiSettingsStack_questions();

};

#endif // GUISETTINGSSTACK_QUESTIONS_H
