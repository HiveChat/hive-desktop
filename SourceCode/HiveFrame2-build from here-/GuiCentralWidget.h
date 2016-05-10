#ifndef GUICENTRALWIDGET_H
#define GUICENTRALWIDGET_H

#include "GuiTabBlock.h"
#include "GuiMainBlock.h"

class GuiCentralWidget : public QWidget
{
  Q_OBJECT

public:
  explicit GuiCentralWidget(QWidget *parent = 0);
  ~GuiCentralWidget();

  QHBoxLayout *main_layout;
  GuiTabBlock *gui_tab_block;
  GuiMainBlock *gui_main_block;

private:
  QString usr_key_str;
  QString usr_name_str;
  QString avatar_path_str;

  QStringList my_profile_str_list;

public slots:
  void addUsr(UsrProfileStruct *usrProfileStruct);
  void delUsr(UsrProfileStruct *usrProfileStruct);

private slots:
  void onUsrProfileChanged(UsrProfileStruct *usrProfileStruct);
  void onMessageCome(MessageStruct *messageStruct, bool fromMe);



};

#endif // GUICENTRALWIDGET_H
