#include "MainBlock.h"

MainBlock::MainBlock(QWidget *parent)
  : QWidget(parent)
  , chat_stack(new ChatStack(this))
  , stacked_widget(new QStackedWidget(this))
{
  this->createStaticStack(GUI::StaticStackType::Home_list);
  this->createStaticStack(GUI::StaticStackType::Home_Welcome);
  this->displayStaticStack(GUI::StaticStackType::Home_Welcome);

  stacked_widget->addWidget(chat_stack);

  QVBoxLayout *main_layout = new QVBoxLayout(this);
  main_layout->setContentsMargins(0,0,0,0);
  main_layout->setSpacing(0);
  main_layout->addWidget(stacked_widget);
}

MainBlock::~MainBlock()
{

}

void MainBlock::clearStackMap(GUI::StaticStackType &reservation)
{
  foreach(GUI::StaticStackType temp_static_stack_type, static_stack_hash.keys())
    {
      if(temp_static_stack_type == GUI::StaticStackType::Home_Welcome
         || temp_static_stack_type == GUI::StaticStackType::Home_list
         || temp_static_stack_type == reservation)
        {
          continue;
        }
      else
        {
          qDebug()<<"#GuiMainBlock::clearStackMap(): Destroyed a QStackedWidget.";
          static_stack_hash.value(temp_static_stack_type)->deleteLater();
          static_stack_hash.remove(temp_static_stack_type);
        }
    }
}

void MainBlock::createStaticStack(GUI::StaticStackType staticStackType)
{
  switch (staticStackType) {
    case GUI::StaticStackType::Home_Welcome:
      {
        home_stack_welcome = new HomeStack_welcome(this);
        static_stack_hash.insert(staticStackType, home_stack_welcome);
        stacked_widget->addWidget(home_stack_welcome);
        stacked_widget->setCurrentWidget(home_stack_welcome);

        return;
      }
    case GUI::StaticStackType::Home_list:
      {
        home_stack_list = new HomeStack_list(this);
        static_stack_hash.insert(staticStackType, home_stack_list);
        stacked_widget->addWidget(home_stack_list);
        stacked_widget->setCurrentWidget(home_stack_list);

        return;
      }
    case GUI::StaticStackType::Home_Storage:
      {
        HomeStack_storage *static_stack = new HomeStack_storage(this);
        static_stack_hash.insert(staticStackType, static_stack);
        stacked_widget->addWidget(static_stack);
        stacked_widget->setCurrentWidget(static_stack);

        return;
      }
    case GUI::StaticStackType::Settings_Messaging:
      {
        SettingsStack_messaging *static_stack = new SettingsStack_messaging(this);
        static_stack_hash.insert(staticStackType, static_stack);
        stacked_widget->addWidget(static_stack);
        stacked_widget->setCurrentWidget(static_stack);

        return;
      }
    case GUI::StaticStackType::Settings_Profile:
      {
        SettingsStack_profile *static_stack = new SettingsStack_profile(this);
        static_stack_hash.insert(staticStackType, static_stack);
        stacked_widget->addWidget(static_stack);
        stacked_widget->setCurrentWidget(static_stack);

        return;
      }
    case GUI::StaticStackType::Settings_Style:
      {

        break;
      }
    case GUI::StaticStackType::Settings_Questions:
      {
        SettingsStack_questions *static_stack = new SettingsStack_questions(this);
        static_stack_hash.insert(staticStackType, static_stack);
        stacked_widget->addWidget(static_stack);
        stacked_widget->setCurrentWidget(static_stack);

        return;
      }
    case GUI::StaticStackType::Settings_Update:
      {
        SettingsStack_update *static_stack = new SettingsStack_update(this);
        static_stack_hash.insert(staticStackType, static_stack);
        stacked_widget->addWidget(static_stack);
        stacked_widget->setCurrentWidget(static_stack);
        break;
      }
    case GUI::StaticStackType::NULL_Stack:
      {
        break;
      }
    }
}

void MainBlock::displayChatStack(const QString &usrKey)
{
  chat_stack->display(usrKey);
  chat_stack->refreshMessage(usrKey);
  stacked_widget->setCurrentWidget(chat_stack);
}

void MainBlock::displayStaticStack(GUI::StaticStackType staticStackType)
{
  if(!static_stack_hash.contains(staticStackType))
      createStaticStack(staticStackType);
  else
      stacked_widget->setCurrentWidget(static_stack_hash.value(staticStackType));
  clearStackMap(staticStackType);

}

void MainBlock::onMessageToSend(QString *usrKey, QString *message)
{
  emit sendMessage(*usrKey, *message);
}
