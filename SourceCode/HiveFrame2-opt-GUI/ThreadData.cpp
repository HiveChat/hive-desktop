#include "ThreadData.h"

ThreadData::ThreadData(QObject *parent) : QThread(parent)
{

}

ThreadData::~ThreadData()
{
  status = false;
}

void ThreadData::run()
{
  this->setPriority(QThread::NormalPriority);

  while(status)
    {

      msleep(1000);
    }
}

void ThreadData::setStatus(bool running)
{
  status = running;
}
