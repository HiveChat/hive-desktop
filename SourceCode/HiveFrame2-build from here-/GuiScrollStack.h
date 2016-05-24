#ifndef GUISCROLLSTACK_H
#define GUISCROLLSTACK_H

#include "GuiAvatarButton.h"
#include "GlobalData.h"

#include <QFormLayout>
#include <QScrollArea>


class GuiScrollStack : public QWidget
{
//  Q_OBJECT

public:
  explicit GuiScrollStack(QWidget *parent = 0);
  ~GuiScrollStack();

  QVBoxLayout *central_layout;

  void setTitle(QString text);
  void setSubTitle(QString text);
  void setIcon(QString path);

protected:
  void setUpUI();
  void addTag(QString text);

  void addItem(QString text, QString string);
  void addItem(QString text, QWidget *widget);
  void addItem(QString text, QLayout *widgetLayout);

  QFont font = GlobalData::font_scrollStackTitle;
  QFont sub_font = GlobalData::font_scrollStackSubtitle;
  QPalette text_palette;
  QPalette sub_text_palette;

  QString title_qstr;
  QString sub_title_qstr;

  GuiAvatarButton *icon_btn;
  QLabel *title_label;
  QHBoxLayout *top_widget_main_layout;

};

#endif // GUISCROLLSTACK_H
