#include "GuiMainBlock.h"

GuiMainBlock::GuiMainBlock(QWidget *parent) : QWidget(parent)
{
  gui_chat_stack = new GuiChatStack(this);
  main_stacked_widget = new QStackedWidget(this);
  main_stacked_widget->addWidget(gui_chat_stack);

  main_layout = new QVBoxLayout(this);
  main_layout->setMargin(0);
  main_layout->setSpacing(0);
  main_layout->addWidget(main_stacked_widget);


  createStaticStack(Home_list);
  createStaticStack(Home_Welcome);
  displayStaticStack(Home_Welcome);

//  connect(gui_chat_stack, SIGNAL(sendMessage(QString*,QString*)), this, SLOT(onMessageToSend(QString*,QString*)));
}

GuiMainBlock::~GuiMainBlock()
{

}

void GuiMainBlock::clearStackMap(StaticStackType &reservation)
{
  foreach (StaticStackType temp_static_stack_type, static_stack_map.keys())
    {
      if(temp_static_stack_type == Home_Welcome
         || temp_static_stack_type == Home_list
         || temp_static_stack_type == reservation)
        {
          continue;
        }
      else
        {
          qDebug()<<"#GuiMainBlock::clearStackMap(): Destroyed a QStackedWidget.";
          QObject *obj = static_stack_map.value(temp_static_stack_type);
          static_stack_map.value(temp_static_stack_type)->deleteLater();
          static_stack_map.remove(temp_static_stack_type);
        }
    }
}

void GuiMainBlock::createStaticStack(StaticStackType staticStackType)
{
  switch (staticStackType) {
    case Home_Welcome:
      {
        gui_home_stack_welcome = new GuiHomeStack_welcome(this);
        static_stack_map.insert(staticStackType, gui_home_stack_welcome);
        main_stacked_widget->addWidget(gui_home_stack_welcome);
        main_stacked_widget->setCurrentWidget(gui_home_stack_welcome);

        return;
      }

    case Home_list:
      {
        gui_home_stack_list = new GuiHomeStack_list(this);
        static_stack_map.insert(staticStackType, gui_home_stack_list);
        main_stacked_widget->addWidget(gui_home_stack_list);
        main_stacked_widget->setCurrentWidget(gui_home_stack_list);

        return;
      }

    ///active stacks
    case Home_Storage:
      {
        GuiHomeStack_storage *static_stack = new GuiHomeStack_storage(this);
        static_stack_map.insert(staticStackType, static_stack);
        main_stacked_widget->addWidget(static_stack);
        main_stacked_widget->setCurrentWidget(static_stack);

        return;
      }

    case Settings_Messaging:
      {
        GuiSettingsStack_messaging *static_stack = new GuiSettingsStack_messaging(this);
        static_stack_map.insert(staticStackType, static_stack);
        main_stacked_widget->addWidget(static_stack);
        main_stacked_widget->setCurrentWidget(static_stack);

        return;
      }
    case Settings_Profile:
      {
        GuiSettingsStack_profile *static_stack = new GuiSettingsStack_profile(this);
        static_stack_map.insert(staticStackType, static_stack);
        main_stacked_widget->addWidget(static_stack);
        main_stacked_widget->setCurrentWidget(static_stack);

        return;
      }

    case Settings_Style:
      {

        break;
      }
    case Settings_Questions:
      {
        GuiSettingsStack_questions *static_stack = new GuiSettingsStack_questions(this);
        static_stack_map.insert(staticStackType, static_stack);
        main_stacked_widget->addWidget(static_stack);
        main_stacked_widget->setCurrentWidget(static_stack);

        return;
      }
    case NULL_Stack:
      {
        break;
      }
    }
}

void GuiMainBlock::displayChatStack(const QString &usrKey)
{
  gui_chat_stack->display(usrKey);
  gui_chat_stack->refreshMessage(usrKey);
  main_stacked_widget->setCurrentWidget(gui_chat_stack);

//  GlobalData::TEST_printUsrProfileStruct(*GlobalData::online_usr_data_map.value(usrKey)->usrProfileStruct(), "GuiMainBlock::displayChatStack");
}

void GuiMainBlock::displayStaticStack(StaticStackType staticStackType)
{
  if(!static_stack_map.contains(staticStackType))
    {
      createStaticStack(staticStackType);
    }
  else
    {
      qDebug()<<"#GuiMainBlock::displayStaticStack(): Displaying Stack that already exist.";
      main_stacked_widget->setCurrentWidget(static_stack_map.value(staticStackType));
    }
  clearStackMap(staticStackType);

}

//GuiChatStack_old* GuiMainBlock::addChatStack(UsrProfileStruct *usrProfileStruct)
//{
//  gui_chat_stack = new GuiChatStack_old(usrProfileStruct, this);
//  main_stacked_widget->addWidget(gui_chat_stack);
//  gui_chat_stack_map.insert(usrProfileStruct->key_str, gui_chat_stack);
//  connect(gui_chat_stack, SIGNAL(sendMessage(QString*,QString*)), this, SLOT(onMessageToSend(QString*,QString*)));
//  return gui_chat_stack;
//}
//<<

void GuiMainBlock::onMessageToSend(QString *usrKey, QString *message)
{
  emit sendMessage(*usrKey, *message);
}




//  QProgressBar {
//      border: 1px solid #FFB500;
//      border-radius: 3px;
//      text-align: center;
//  }

//  QProgressBar::chunk {
//      background-color: #FFB500;

//  }
