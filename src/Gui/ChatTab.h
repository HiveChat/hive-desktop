#ifndef GUICHATTAB_H
#define GUICHATTAB_H

#include "Gui/Frameworks/CombWidget.h"
#include "UsrData.h"

#include <QScrollArea>
#include <QDrag>

class CombScrollWidget;
class ChatTab;

class CombScrollWidget : public QWidget
{
  Q_OBJECT

public:
  explicit CombScrollWidget(QWidget *parent = nullptr);
  void addComb(UsrProfile *p);
  void refreshComb(UsrProfile *p);
  void refreshBadgeNumber(const QString &uuid, const int &num);
  bool contains(const QString &uuid);

  void onCombWidgetClicked(const QString &uuid);

private:
  QVBoxLayout *main_layout;
  QHash<QString, CombWidget *> comb_widget_hash;

signals:
  void combWidgetClicked(const QString &uuid);
};

class ChatTab : public QScrollArea
{
  Q_OBJECT
public:
  explicit ChatTab(QWidget *parent = nullptr);
  CombScrollWidget *comb_scroll_widget;
};

#endif // GUICHATTAB_H
