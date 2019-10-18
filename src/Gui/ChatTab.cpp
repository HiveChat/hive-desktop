#include "ChatTab.h"
#include <QApplication>
#include <QMenu>
#include <QDebug>
#include <QScrollBar>

ChatTab::ChatTab(QWidget *parent)
  : QScrollArea(parent)
{
//  this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  this->setFrameShape(QFrame::NoFrame);
  this->setWidgetResizable(true);
  comb_scroll_widget = new CombScrollWidget();
  this->setWidget(comb_scroll_widget);

  QPalette palette;
  palette.setColor(QPalette::Window, Qt::transparent);
  this->setAutoFillBackground(true);
  this->setPalette(palette);
  this->setFixedWidth(250);
}

CombScrollWidget::CombScrollWidget(QWidget *parent)
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

void CombScrollWidget::addComb(UsrProfile *p)
{
  Log::gui(Log::Info, "GuiChatTab_comb_scroll_widget::addComb()", "Added a comb.");

  CombWidget *w = new CombWidget(p, this);
  comb_widget_hash.insert(p->key, w);
  main_layout->addWidget(w);

  connect(w, &CombWidget::clicked,
          [this](const QString &uuid){
            emit combWidgetClicked(uuid);
          });
}

void CombScrollWidget::refreshBadgeNumber(const QString &uuid, const int &num)
{
  CombWidget *comb_widget = comb_widget_hash.value(uuid);
  qDebug()<<"badge:" <<num;
  comb_widget->setBadgeNumber(num);
  if(num != 0)
    {
      main_layout->takeAt(main_layout->indexOf(comb_widget));
      main_layout->insertWidget(0, comb_widget);
    }
}

bool CombScrollWidget::contains(const QString &uuid)
{
  return comb_widget_hash.contains(uuid);
}


void CombScrollWidget::refreshComb(UsrProfile *p)
{
  CombWidget *comb_widget = comb_widget_hash.value(p->key);
  if(comb_widget != nullptr)
    {
      comb_widget->setProfile(p);
    }
  else
    {
      qDebug()<<"Something Impossible happened!!!";
    }
}

void CombScrollWidget::onCombWidgetClicked(const QString &uuid)
{
  emit combWidgetClicked(uuid);
}
