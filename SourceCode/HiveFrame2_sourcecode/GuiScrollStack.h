#ifndef GUISCROLLSTACK_H
#define GUISCROLLSTACK_H

#include "GuiAvatarButton.h"
#include "GlobalData.h"

#include <QFrame>
#include <QVBoxLayout>
#include <QScrollArea>


class GuiScrollStack : public QWidget
{
  Q_OBJECT

  enum LayoutStyle
  {
    Profile,
    Linear
  };

public:
  explicit GuiScrollStack(QWidget *parent = 0);

  explicit GuiScrollStack(LayoutStyle &layout_style, QWidget *parent = 0);
  ~GuiScrollStack();

  QVBoxLayout *central_layout;


protected:
  void setUpUI();
  void setTitle(const QString &text);
  void setSubTitle(const QString &text);
  void setIcon(const QString &path);
  void addTag(const QString &text);
  void addItem(const QString &text, QString string);
  void addItem(const QString &text, QWidget *widget);
  void addItem(const QString &text, QLayout *widgetLayout);
  void addItem(QWidget *centralWidget);

  QFont font = GlobalData::font_scrollStackTitle;
  QFont sub_font = GlobalData::font_scrollStackSubtitle;
  QPalette text_palette;
  QPalette sub_text_palette;

  QString title_qstr;
  QString sub_title_qstr;

  GuiAvatarButton *icon_btn;
  QLabel *title_label;
  QHBoxLayout *top_frame_main_layout;

};

#endif // GUISCROLLSTACK_H
