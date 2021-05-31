#include "SideBar.h"
#include <QFileDialog>
#include <QLabel>

SideBar::SideBar(QWidget *parent)
  : QWidget(parent)
  , home_tab(new HomeTab(this))
  , contacts_tab(new ContactsTab(this))
  , settings_tab(new SettingsTab(this))
  , tab_stacked_widget(new QStackedWidget(this))
{
  this->setAutoFillBackground(true);
  QPalette palette;
  palette.setColor(QPalette::Window, Global::color_alphaTab);
  this->setPalette(palette);
  this->setFixedWidth(250);

  tab_stacked_widget->addWidget(contacts_tab);
  tab_stacked_widget->addWidget(home_tab);
  tab_stacked_widget->addWidget(settings_tab);

  search_bar = new SearchBar(this);
  connect(search_bar, &SearchBar::settingsSelected, this, &SideBar::displaySettings);

  QVBoxLayout *mainLayout = new QVBoxLayout(this);
  mainLayout->setSpacing(0);
  mainLayout->setContentsMargins(0,0,0,0);
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
    tab_stacked_widget->setCurrentWidget(contacts_tab);
}

void SideBar::displayHome()
{
  tab_stacked_widget->setCurrentWidget(home_tab);
}

void SideBar::displayChat()
{
  tab_stacked_widget->setCurrentWidget(contacts_tab);
}



