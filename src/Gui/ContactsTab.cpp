#include "ContactsTab.h"
#include <QApplication>
#include <QMenu>
#include <QDebug>
#include <QScrollBar>

ContactsTab::ContactsTab(QWidget *parent)
  : QScrollArea(parent)
{
//  this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  this->setFrameShape(QFrame::NoFrame);
  this->setWidgetResizable(true);
  contact_scroll_widget = new ContactsScrollWidget();
  this->setWidget(contact_scroll_widget);

  QPalette palette;
  palette.setColor(QPalette::Window, Qt::transparent);
  this->setAutoFillBackground(true);
  this->setPalette(palette);
  this->setFixedWidth(250);
}

ContactsScrollWidget::ContactsScrollWidget(QWidget *parent)
  : QWidget(parent)
{
  QPalette palette;
  palette.setColor(QPalette::Window, Qt::transparent);
  this->setPalette(palette);
  this->setAutoFillBackground(true);

  ///main layout
  main_layout = new QVBoxLayout(this);
  main_layout->setAlignment(Qt::AlignTop);
  main_layout->setContentsMargins(0,0,0,0);
  main_layout->setSpacing(0);
}

void ContactsScrollWidget::addComb(UsrProfile *p)
{
  Log::gui(Log::Info, "CombScrollWidget::addComb()", "Added a contact.");

  ContactWidget *w = new ContactWidget(p, this);
  contact_widget_hash.insert(p->key, w);
  main_layout->addWidget(w);

  connect(w, &ContactWidget::clicked,
          [this](const QString &uuid){
            emit contactWidgetClicked(uuid);
          });
}

void ContactsScrollWidget::refreshBadgeNumber(const QString &uuid, const int &num)
{
  ContactWidget *contactWidget = contact_widget_hash.value(uuid);
  qDebug()<<"badge:" <<num;
  contactWidget->setBadgeNumber(num);
  if(num != 0)
    {
      main_layout->takeAt(main_layout->indexOf(contactWidget));
      main_layout->insertWidget(0, contactWidget);
    }
}

bool ContactsScrollWidget::contains(const QString &uuid)
{
  return contact_widget_hash.contains(uuid);
}


void ContactsScrollWidget::refreshComb(UsrProfile *p)
{
  ContactWidget *contactWidget = contact_widget_hash.value(p->key);
  if(contactWidget != nullptr)
    {
      contactWidget->setProfile(p);
    }
  else
    {
      qDebug()<<"Something Impossible happened!!!";
    }
}

void ContactsScrollWidget::onCombWidgetClicked(const QString &uuid)
{
  emit contactWidgetClicked(uuid);
}
