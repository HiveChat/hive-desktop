#ifndef GUISETTINGSSTACK_QUESTIONS_H
#define GUISETTINGSSTACK_QUESTIONS_H

#include "Gui/Frameworks/ScrollStack.h"
#include "GlobalData.h"

class SettingsStack_questions : public ScrollStack
{
  Q_OBJECT

public:
  explicit SettingsStack_questions(QWidget *parent = 0);
  ~SettingsStack_questions();

};

#endif // GUISETTINGSSTACK_QUESTIONS_H
