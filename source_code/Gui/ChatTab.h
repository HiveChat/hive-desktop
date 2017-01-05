#ifndef GUICHATTAB_H
#define GUICHATTAB_H

#include "Gui/Frameworks/CombWidget.h"
#include "UsrData.h"

#include <QScrollArea>
#include <QHash>

class ChatTab_comb_scroll_widget;
class ChatTab;

class ChatTab_comb_scroll_widget : public QWidget
{
  Q_OBJECT

public:
  explicit ChatTab_comb_scroll_widget(QWidget *parent = 0);
  void addComb(UsrProfileStruct *usrProfileStruct);
  void refreshComb(UsrProfileStruct *usrProfileStruct);
  void refreshBadgeNumber(const QString &usrKey, const int &num);

private:
  QVBoxLayout *main_layout;
  QHash<QString, GuiCombWidget *> comb_widget_hash;

signals:
  void combWidgetClicked(const QString &usrKey);

public slots:
  void onCombWidgetClicked(const QString &usrKey);


};

class ChatTab : public QWidget
{
  Q_OBJECT

public:
  explicit ChatTab(QWidget *parent = 0);
  QScrollArea *comb_scrollarea;
  ChatTab_comb_scroll_widget *comb_scroll_widget;

private:
  QVBoxLayout *main_layout;
  QVBoxLayout *comb_layout;

};

#endif // GUICHATTAB_H
