#ifndef GUISCROLLSTACK_H
#define GUISCROLLSTACK_H

#include <QFormLayout>
#include <QScrollArea>
#include <GuiAvatarButton.h>


class GuiScrollStack : public QWidget
{
  Q_OBJECT

public:
  explicit GuiScrollStack(QWidget *parent = 0);
  ~GuiScrollStack();

  QVBoxLayout *central_layout;

  void setTitle(QString text);
  void setSubTitle(QString text);
  void setIcon(QString path);

private:
  GuiAvatarButton *icon_btn;
  QLabel *title_label;
  QLabel *sub_title_label;
  QHBoxLayout *top_widget_main_layout;


};

#endif // GUISCROLLSTACK_H
