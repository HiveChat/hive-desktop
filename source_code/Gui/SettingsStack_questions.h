#ifndef GUISETTINGSSTACK_QUESTIONS_H
#define GUISETTINGSSTACK_QUESTIONS_H

#include "Gui/Frameworks/ScrollStack.h"
#include "GlobalData.h"

class GuiSettingsStack_questions : public ScrollStack
{
  Q_OBJECT

public:
  explicit GuiSettingsStack_questions(QWidget *parent = 0);
  ~GuiSettingsStack_questions();

};

#endif // GUISETTINGSSTACK_QUESTIONS_H
