#ifndef GUICHATTAB_H
#define GUICHATTAB_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QLineEdit>
#include <QPalette>
#include <QScrollArea>

#include "GuiCombWidget.h"

class GuiChatTab_comb_scroll_widget : public QWidget
{
  Q_OBJECT

public:
  explicit GuiChatTab_comb_scroll_widget(QWidget *parent = 0);

private:
  QVBoxLayout *main_layout;

};

class GuiChatTab : public QWidget
{
  Q_OBJECT

public:
  explicit GuiChatTab(QWidget *parent = 0);

  void addNewComb(QString);
  void addNewGroup(QString);

signals:

public slots:

private:
  QVBoxLayout *main_layout;
  QVBoxLayout *comb_layout;
  QScrollArea *comb_scrollarea;

  //QTreeWidget *comb_treewidget;
  //QTreeWidgetItem *comb_treewidget_item;

private slots:
  void onItemClicked(QTreeWidgetItem *item, int column);
  void showMenu();

};

#endif // GUICHATTAB_H
