#include "SideBar.h"
#include <QFileDialog>
#include <QLabel>

SideBar::SideBar(QWidget *parent)
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
  connect(search_bar, &SearchBar::settingsSelected, this, &SideBar::displaySettings);

  QVBoxLayout *mainLayout = new QVBoxLayout(this);
  mainLayout->setSpacing(0);
  mainLayout->setMargin(0);
  mainLayout->setAlignment(Qt::AlignTop);
  mainLayout->addSpacing(5);
  mainLayout->addWidget(search_bar);
  mainLayout->addSpacing(5);
  mainLayout->addWidget(tab_stacked_widget);

}

SideBar::~SideBar()
{

}

void SideBar::displaySettings(const bool& b)
{
  if(b)
    tab_stacked_widget->setCurrentWidget(settings_tab);
  else
    tab_stacked_widget->setCurrentWidget(chat_tab);
}

void SideBar::displayHome()
{
  tab_stacked_widget->setCurrentWidget(home_tab);
}

void SideBar::displayChat()
{
  tab_stacked_widget->setCurrentWidget(chat_tab);
}



