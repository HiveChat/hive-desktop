#ifndef THREADINFO_H
#define THREADINFO_H

#include "GlobalData.h"

#include <QThread>
#include <QDebug>
#include <QCoreApplication>

class ThreadInfo : public QThread
{
  Q_OBJECT

public:
  explicit ThreadInfo(QObject *parent = 0);
  ~ThreadInfo();

protected:
  void run();

private:
  void checkGlobalData();

  QColor b_mChatBubbleColorI;
  QColor b_mChatBubbleColorO;
  QString b_myNameStr;
  QString b_avatarPathStr;

signals:
  void globalDataChanged();

};

#endif // THREADINFO_H
