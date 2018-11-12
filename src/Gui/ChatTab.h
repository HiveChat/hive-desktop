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
  void refreshBadgeNumber(const QString &usrKey, const int &num);
  bool contains(const QString &usrKey);

  void onCombWidgetClicked(const QString &usrKey);

private:
  QVBoxLayout *main_layout;
  QHash<QString, CombWidget *> comb_widget_hash;

signals:
  void combWidgetClicked(const QString &usrKey);
};

class ChatTab : public QWidget
{
  Q_OBJECT
public:
  explicit ChatTab(QWidget *parent = nullptr);
  QScrollArea *comb_scrollarea;
  CombScrollWidget *comb_scroll_widget;

private:
  QVBoxLayout *main_layout;
  QVBoxLayout *comb_layout;
};

#endif // GUICHATTAB_H
