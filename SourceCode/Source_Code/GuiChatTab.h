#ifndef GUICHATTAB_H
#define GUICHATTAB_H

#include "GuiCombWidget.h"
#include "UsrData.h"

#include <QScrollArea>
#include <QMap>


class GuiChatTab_comb_scroll_widget : public QWidget
{
  Q_OBJECT

public:
  explicit GuiChatTab_comb_scroll_widget(QWidget *parent = 0);
  void refreshComb(UsrProfileStruct *usrProfileStruct);
  void addComb(UsrProfileStruct *usrProfileStruct);
  void setBadgeNumber(const QString &usrKey, const int &num);

private:
  QVBoxLayout *main_layout;
  QMap<QString, GuiCombWidget *> comb_widget_map;

signals:
  void combWidgetClicked(QString usrKey);

public slots:
  void onCombWidgetClicked(QString usrKey);


};

///////////

class GuiChatTab : public QWidget
{
  Q_OBJECT

public:
  explicit GuiChatTab(QWidget *parent = 0);
  QScrollArea *comb_scrollarea;
  GuiChatTab_comb_scroll_widget *comb_scroll_widget;

private:
  QVBoxLayout *main_layout;
  QVBoxLayout *comb_layout;


private slots:
  void showMenu();

};

#endif // GUICHATTAB_H
