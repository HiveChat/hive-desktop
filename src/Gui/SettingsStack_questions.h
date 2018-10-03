#ifndef GUISETTINGSSTACK_QUESTIONS_H
#define GUISETTINGSSTACK_QUESTIONS_H

#include "Gui/Frameworks/ScrollStack.h"
#include "Global.h"

class SettingsStack_questions : public ScrollStack
{
  Q_OBJECT

public:
  explicit SettingsStack_questions(QWidget *parent = nullptr);
  ~SettingsStack_questions();

};

#endif // GUISETTINGSSTACK_QUESTIONS_H
