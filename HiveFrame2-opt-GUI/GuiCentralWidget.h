#ifndef GUICENTRALWIDGET_H
#define GUICENTRALWIDGET_H

#include "GuiTabBlock.h"
#include "GuiMainBlock.h"

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QStackedWidget>
#include <QTabWidget>

class GuiCentralWidget : public QWidget
{
  Q_OBJECT

public:
  explicit GuiCentralWidget(QWidget *parent = 0);
  ~GuiCentralWidget();

  QHBoxLayout *main_layout;
  GuiTabBlock *gui_tab_block;
  GuiMainBlock *gui_main_block;
};

#endif // GUICENTRALWIDGET_H
