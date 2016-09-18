#ifndef GUISCROLLSTACK_H
#define GUISCROLLSTACK_H

#include "GuiAvatarButton.h"
#include "GlobalData.h"

#include <QFrame>
#include <QVBoxLayout>
#include <QScrollArea>

enum LayoutStyle
{
  Profile,
  Linear
};


class GuiScrollStack : public QWidget
{
  Q_OBJECT

public:
  explicit GuiScrollStack(QWidget *parent = 0);
  ~GuiScrollStack();



protected:
  void setUpUI(const LayoutStyle &layoutStyle);
  void setTitle(const QString &text);
  void setSubTitle(const QString &text);
  void setIcon(const QString &path);
  void addTag(const QString &text);
  void addItem(const QString &text, const QString &string, const bool &wrapping = true);
  void addItem(const QString &text, QWidget *widget);
  void addItem(const QString &text, QLayout *widgetLayout);
  void addItem(QWidget *centralWidget);

  QFont font = GlobalData::font_scrollStackTitle;
  QFont sub_font = GlobalData::font_scrollStackSubtitle;
  QPalette text_palette;
  QPalette sub_text_palette;

  QString title_qstr = "";
  QString sub_title_qstr = "";
  LayoutStyle layout_style = LayoutStyle::Linear;

  GuiAvatarButton *icon_btn;
  QLabel *composite_title_label;
  QLabel *title_label;
  QLabel *sub_title_label;
  QScrollArea *scroll_area;
  QHBoxLayout *top_frame_main_layout;
  QVBoxLayout *central_layout;
  QVBoxLayout *main_layout;
};

#endif // GUISCROLLSTACK_H
