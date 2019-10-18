#ifndef GUICHATTAB_H
#define GUICHATTAB_H

#include "Gui/Frameworks/ContactWidget.h"
#include "UsrData.h"

#include <QScrollArea>
#include <QDrag>

class ContactsScrollWidget;
class ContactsTab;

class ContactsScrollWidget : public QWidget
{
  Q_OBJECT

public:
  explicit ContactsScrollWidget(QWidget *parent = nullptr);
  void addComb(UsrProfile *p);
  void refreshComb(UsrProfile *p);
  void refreshBadgeNumber(const QString &uuid, const int &num);
  bool contains(const QString &uuid);

  void onCombWidgetClicked(const QString &uuid);

private:
  QVBoxLayout *main_layout;
  QHash<QString, ContactWidget *> contact_widget_hash;

signals:
  void contactWidgetClicked(const QString &uuid);
};

class ContactsTab : public QScrollArea
{
  Q_OBJECT
public:
  explicit ContactsTab(QWidget *parent = nullptr);
  ContactsScrollWidget *contact_scroll_widget;
};

#endif // GUICHATTAB_H
