#include "GuiMainBlock.h"

GuiMainBlock::GuiMainBlock(QWidget *parent) : QWidget(parent)
{

  main_stacked_widget = new QStackedWidget(this);


  main_layout = new QVBoxLayout(this);
  main_layout->setMargin(0);
  main_layout->setSpacing(0);
  main_layout->addWidget(main_stacked_widget);

  displayStaticStack(Home_Welcome);
}

GuiMainBlock::~GuiMainBlock()
{

}

void GuiMainBlock::clearStackMap(StaticStackType *reservation)
{
  foreach (StaticStackType temp_static_stack_type, static_stack_map.keys())
    {
      if(temp_static_stack_type == Home_Welcome
         || temp_static_stack_type == *reservation)
        {
          continue;
        }
      else
        {
          qDebug()<<"#GuiMainBlock::clearStackMap(): Destroyed a QStackedWidget.";
          static_stack_map.value(temp_static_stack_type)->deleteLater();
          static_stack_map.remove(temp_static_stack_type);
        }
    }
}


void GuiMainBlock::displayChatStack(QString usrKey)
{
  main_stacked_widget->setCurrentWidget(gui_chat_stack_map.find(usrKey).value());
}



void GuiMainBlock::displayStaticStack(StaticStackType staticStackType)
{
  if(!static_stack_map.contains(staticStackType))
    {
      switch (staticStackType) {
        case Home_Welcome:
          {
            gui_home_stack_welcome = new GuiHomeStack_welcome(this);
            static_stack_map.insert(staticStackType, gui_home_stack_welcome);
            main_stacked_widget->addWidget(gui_home_stack_welcome);
            main_stacked_widget->setCurrentWidget(gui_home_stack_welcome);

            break;
          }

        case Home_list:
          {
            gui_home_stack_list = new GuiHomeStack_list(this);
            static_stack_map.insert(staticStackType, gui_home_stack_list);
            main_stacked_widget->addWidget(gui_home_stack_list);
            main_stacked_widget->setCurrentWidget(gui_home_stack_list);

            break;
          }

        case Home_Storage:
          {
            GuiHomeStack_storage *gui_home_stack = new GuiHomeStack_storage(this);
            static_stack_map.insert(staticStackType, gui_home_stack);
            main_stacked_widget->addWidget(gui_home_stack);
            main_stacked_widget->setCurrentWidget(gui_home_stack);

            break;
          }

        case Settings_Messaging:
          {
            GuiSettingsStack_messaging *gui_settings_stack = new GuiSettingsStack_messaging(this);
            static_stack_map.insert(staticStackType, gui_settings_stack);
            main_stacked_widget->addWidget(gui_settings_stack);
            main_stacked_widget->setCurrentWidget(gui_settings_stack);

            break;
          }
        case Settings_Profile:
          {
            GuiSettingsStack_profile *gui_settings_stack = new GuiSettingsStack_profile(this);
            static_stack_map.insert(staticStackType, gui_settings_stack);
            main_stacked_widget->addWidget(gui_settings_stack);
            main_stacked_widget->setCurrentWidget(gui_settings_stack);

            break;
          }

        case Settings_Style:
          {

            break;
          }
        case Settings_Questions:
          {
            GuiSettingsStack_questions *gui_settings_stack = new GuiSettingsStack_questions(this);
            static_stack_map.insert(staticStackType, gui_settings_stack);
            main_stacked_widget->addWidget(gui_settings_stack);
            main_stacked_widget->setCurrentWidget(gui_settings_stack);

            break;
          }

        default:
          {
            break;
          }
        }
    }
  else
    {
      qDebug()<<"GuiMainBlock::displayStaticStack(): Displaying Stack that already exist.";
      main_stacked_widget->setCurrentWidget(static_stack_map.value(staticStackType));
    }

  clearStackMap(&staticStackType);



  ///2016-02-16 LAZY SOLUTION HINT make a QMap to match each static stacks to the enum value, this means static stacks should be in the class definition. This must works, but might not be the best algorithm.

  ///is not current stack || is the first stack, which means is not current stack
//  if(staticStackType != current_static_stack_type)
//    {
//      ///static_stack_list is not nullptr
//      ///MEANS this is not the first stack
//      if(static_stack_widget != NULL)
//        {
//          static_stack_widget->deleteLater();
//        }

//      switch (staticStackType) {
//        case Home_Welcome:
//          {
//            static_stack_widget = gui_home_stack_welcome;
//            main_stacked_widget->addWidget(gui_home_stack_welcome);
//            main_stacked_widget->setCurrentWidget(gui_home_stack_welcome);

//            break;
//          }

//        case Home_list:
//          {
//            gui_home_stack_list = new GuiHomeStack_list(this);
//            static_stack_widget = gui_home_stack_list;
//            main_stacked_widget->addWidget(gui_home_stack_list);
//            main_stacked_widget->setCurrentWidget(gui_home_stack_list);

//            break;
//          }

//        case Home_Storage:
//          {
//            GuiHomeStack_storage *gui_home_stack = new GuiHomeStack_storage(this);
//            static_stack_widget = gui_home_stack;
//            main_stacked_widget->addWidget(gui_home_stack);
//            main_stacked_widget->setCurrentWidget(gui_home_stack);

//            break;
//          }

//        case Settings_Messaging:
//          {
//            GuiSettingsStack_messaging *gui_settings_stack = new GuiSettingsStack_messaging(this);
//            static_stack_widget = gui_settings_stack;
//            main_stacked_widget->addWidget(gui_settings_stack);
//            main_stacked_widget->setCurrentWidget(gui_settings_stack);

//            break;
//          }
//        case Settings_Profile:
//          {
//            GuiSettingsStack_profile *gui_settings_stack = new GuiSettingsStack_profile(this);
//            static_stack_widget = gui_settings_stack;
//            main_stacked_widget->addWidget(gui_settings_stack);
//            main_stacked_widget->setCurrentWidget(gui_settings_stack);

//            break;
//          }

//        case Settings_Style:
//          {

//            break;
//          }
//        case Settings_Questions:
//          {
//            GuiSettingsStack_questions *gui_settings_stack = new GuiSettingsStack_questions(this);
//            static_stack_widget = gui_settings_stack;
//            main_stacked_widget->addWidget(gui_settings_stack);
//            main_stacked_widget->setCurrentWidget(gui_settings_stack);

//            break;
//          }

//        default:
//          {
//            break;
//          }
//        }

//      current_static_stack_type = staticStackType;
//    }
//  else
//    {
//      qDebug()<<"GuiMainBlock::displayStaticStack(): Already displayed.";
//      main_stacked_widget->setCurrentWidget(static_stack_widget);
//    }
}

GuiChatStack* GuiMainBlock::addChatStack(UsrProfileStruct *usrProfileStruct)
{
  gui_chat_stack = new GuiChatStack(usrProfileStruct, this);
  main_stacked_widget->addWidget(gui_chat_stack);
  gui_chat_stack_map.insert(usrProfileStruct->key_str, gui_chat_stack);
  connect(gui_chat_stack, SIGNAL(sendMessage(QString*,QString*)), this, SLOT(onMessageToSend(QString*,QString*)));
  connect(gui_chat_stack->message_editor, SIGNAL(sendMessage(QString*,QString*)), this, SLOT(onMessageToSend(QString*,QString*)));
  return gui_chat_stack;
}

void GuiMainBlock::onMessageRecieved(MessageStruct messageStruct, bool fromMe)
{
  if(fromMe)
    {
      gui_chat_stack_map.find(messageStruct.reciever_key).value()->checkMessage(messageStruct, fromMe);
    }
  else
    {
      gui_chat_stack_map.find(messageStruct.sender_key).value()->checkMessage(messageStruct, fromMe);
    }
}

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
