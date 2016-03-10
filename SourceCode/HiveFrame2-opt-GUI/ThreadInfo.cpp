#include "ThreadInfo.h"


ThreadInfo::ThreadInfo(QObject *parent) : QThread(parent)
{
  this->start(QThread::LowestPriority);

  b_mChatBubbleColorI = GlobalData::g_mChatBubbleColorI;
  b_mChatBubbleColorO = GlobalData::g_mChatBubbleColorO;
  b_myNameStr = GlobalData::g_myNameStr;
  b_avatarPathStr = GlobalData::g_avatarPathStr;

  this->setParent(parent);
}

ThreadInfo::~ThreadInfo()
{

}

void ThreadInfo::run()
{
  while(true)
    {
      checkGlobalData();
      checkNetConnection();

      QCoreApplication::processEvents();
      msleep(1000);
    }
}

void ThreadInfo::checkGlobalData()
{
  qDebug()<<"invoke: void ThreadInfo::checkGlobalData()";
  if(b_mChatBubbleColorI != GlobalData::g_mChatBubbleColorI ||
     b_mChatBubbleColorO != GlobalData::g_mChatBubbleColorO ||
     b_myNameStr != GlobalData::g_myNameStr ||
     b_avatarPathStr != GlobalData::g_avatarPathStr)
    {
      b_mChatBubbleColorI = GlobalData::g_mChatBubbleColorI;
      b_mChatBubbleColorO = GlobalData::g_mChatBubbleColorO;
      b_myNameStr = GlobalData::g_myNameStr;
      b_avatarPathStr = GlobalData::g_avatarPathStr;
      emit globalDataChanged();
    }
}

void ThreadInfo::checkNetConnection()
{
  NetManager::refreshLocalHostIP();
}

