#include "GuiSettingsStack_questions.h"


GuiSettingsStack_questions::GuiSettingsStack_questions(QWidget *parent)// : QWidget(parent)
{
  setIcon(":/img/img/question.png");
  setTitle("Settings");
  setSubTitle("questions");
  setTag("About Hive!");

  addItem("Author:", "Tim Zheng");
//  addItem("");

  this->setParent(parent);
}

GuiSettingsStack_questions::~GuiSettingsStack_questions()
{

}

