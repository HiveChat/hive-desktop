#ifndef GUISCROLLSTACK_H
#define GUISCROLLSTACK_H

#include "Gui/Frameworks/Widgets/AvatarWidgets.h"
#include "Log.h"
#include "Global.h"

#include <QFrame>
#include <QVBoxLayout>
#include <QScrollArea>

enum LayoutStyle
{
  Profile,
  Linear
};


class ScrollStack : public QWidget
{
  Q_OBJECT

public:
  explicit ScrollStack(QWidget *parent = nullptr);
  ~ScrollStack();



protected:
  void setUpUI(const LayoutStyle &layoutStyle);
  void setTitle(const QString &text);
  void setSubTitle(const QString &text);
  void setIcon(const QString &path);
  QLabel *addTag(const QString &text);
  QBoxLayout *addItem(const QString &text, const QString &string, const bool &wrapping = true);
  QBoxLayout *addItem(const QString &text, QLayout *widgetLayout);
  QBoxLayout *addItem(const QString &text, QWidget *widget);
  QBoxLayout *addItem(QWidget *widget, const QString &text);
  void addItem(QWidget *centralWidget);

  QFont font = Global::font_scrollStackTitle;
  QFont sub_font = Global::font_scrollStackSubtitle;
  QPalette text_palette;
  QPalette sub_text_palette;

  QString title_qstr = "";
  QString sub_title_qstr = "";
  LayoutStyle layout_style = LayoutStyle::Linear;

  AvatarButton *icon_btn;
  QLabel *composite_title_label;
  QLabel *title_label;
  QLabel *sub_title_label;
  QScrollArea *scroll_area;
  QHBoxLayout *top_frame_main_layout;
  QVBoxLayout *central_layout;
  QVBoxLayout *main_layout;
};

#endif // GUISCROLLSTACK_H
