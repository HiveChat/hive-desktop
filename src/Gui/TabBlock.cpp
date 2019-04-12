#include "TabBlock.h"
#include <QFileDialog>
#include <QLabel>

TabBlock::TabBlock(QWidget *parent)
  : QWidget(parent)
  , home_tab(new HomeTab(this))
  , chat_tab(new ChatTab(this))
  , settings_tab(new SettingsTab(this))
  , tab_stacked_widget(new QStackedWidget(this))
{
  this->setAutoFillBackground(true);
  QPalette palette;
  palette.setColor(QPalette::Window, Global::color_alphaTab);
  this->setPalette(palette);
  this->setFixedWidth(250);

  tab_stacked_widget->addWidget(chat_tab);
  tab_stacked_widget->addWidget(home_tab);
  tab_stacked_widget->addWidget(settings_tab);

  search_bar = new SearchBar(this);
  connect(search_bar, &SearchBar::settingsClicked, this, &TabBlock::displaySettings);

  QVBoxLayout *main_layout = new QVBoxLayout(this);
  main_layout->setSpacing(0);
  main_layout->setMargin(0);
  main_layout->setAlignment(Qt::AlignTop);
  main_layout->addSpacing(5);
  main_layout->addWidget(search_bar);
  main_layout->addWidget(tab_stacked_widget);

}

TabBlock::~TabBlock()
{

}

void TabBlock::displaySettings()
{
  tab_stacked_widget->setCurrentWidget(settings_tab);
}

void TabBlock::displayHome()
{
  tab_stacked_widget->setCurrentWidget(home_tab);
}

void TabBlock::displayChat()
{
  tab_stacked_widget->setCurrentWidget(chat_tab);
}



