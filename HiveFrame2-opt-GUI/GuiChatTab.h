#ifndef GUICHATTAB_H
#define GUICHATTAB_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QLineEdit>
#include <QPalette>


class GuiChatTab : public QWidget
{
  Q_OBJECT

public:
  explicit GuiChatTab(QWidget *parent = 0);
  ~GuiChatTab();

  void addNewComb(QString);
  void addNewGroup(QString);

signals:

public slots:

private:
  QVBoxLayout *main_layout;
  QTreeWidget *comb_treewidget;
  QTreeWidgetItem *comb_treewidget_item;

private slots:
  void onItemClicked(QTreeWidgetItem *item, int column);
  void showMenu();

};

#endif // GUICHATTAB_H
