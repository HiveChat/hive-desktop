#ifndef THREADFILETCP_H
#define THREADFILETCP_H

#include <QThread>

class ThreadFileTCP : public QThread
{
  Q_OBJECT
public:
  explicit ThreadFileTCP(QObject *parent = 0);

};

#endif // THREADFILETCP_H
