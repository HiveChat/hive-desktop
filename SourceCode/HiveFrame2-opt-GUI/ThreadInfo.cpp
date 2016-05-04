#include "ThreadInfo.h"


ThreadInfo::ThreadInfo(QObject *parent) : QThread(parent)
{
  this->start(QThread::LowestPriority);



  this->setParent(parent);
}

ThreadInfo::~ThreadInfo()
{
  running = false;
}

void ThreadInfo::run()
{
  while(running)
    {
      checkNetConnection();

      msleep(1000);
    }
}



void ThreadInfo::checkNetConnection()
{
//  qDebug()<<"invoke: void NetManager::refreshLocalHostIP()";
}

