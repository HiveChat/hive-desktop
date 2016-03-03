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

protected:
  void setUpUI();
  void setTag(QString text);

  void addItem(QString text, QString string);
  void addItem(QString text, QWidget *widget);
  void addItem(QString text, QLayout *widgetLayout);

  QFont sub_font;
  QFont font;
  QPalette text_palette;
  QPalette sub_text_palette;

  QString title_qstr;
  QString sub_title_qstr;

  GuiAvatarButton *icon_btn;
  QLabel *title_label;
  QHBoxLayout *top_widget_main_layout;

};

#endif // GUISCROLLSTACK_H
