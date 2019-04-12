#ifndef GUITABBLOCK_H
#define GUITABBLOCK_H

#include "Gui/Frameworks/Widgets/Button.h"
#include "Gui/Frameworks/Widgets/SearchBar.h"

#include "ChatTab.h"
#include "HomeTab.h"
#include "SettingsTab.h"

#include <QStackedWidget>
#include <QLineEdit>
#include <QIcon>


class TabBlock : public QWidget
{
  Q_OBJECT

public:
  explicit TabBlock(QWidget *parent = nullptr);
  ~TabBlock();

  void displaySettings();
  void displayHome();
  void displayChat();

  HomeTab *home_tab;
  ChatTab *chat_tab;
  SettingsTab *settings_tab;

private:
  QStackedWidget *tab_stacked_widget;
  SearchBar *search_bar;
};

#endif // GUITABBLOCK_H
