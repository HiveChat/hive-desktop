#include "ThreadInfo.h"


ThreadInfo::ThreadInfo(QObject *parent) : QThread(parent)
{
  this->start(QThread::LowestPriority);

  b_mChatBubbleColorI = GlobalData::g_mChatBubbleColorI;
  b_mChatBubbleColorO = GlobalData::g_mChatBubbleColorO;
  b_myNameStr = GlobalData::g_my_profile.name_str;
  b_avatarPathStr = GlobalData::g_my_profile.avatar_str;

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
//  qDebug()<<"invoke: void ThreadInfo::checkGlobalData()";
  if(b_mChatBubbleColorI != GlobalData::g_mChatBubbleColorI ||
     b_mChatBubbleColorO != GlobalData::g_mChatBubbleColorO ||
     b_myNameStr != GlobalData::g_my_profile.name_str ||
     b_avatarPathStr != GlobalData::g_my_profile.avatar_str)
    {
      b_mChatBubbleColorI = GlobalData::g_mChatBubbleColorI;
      b_mChatBubbleColorO = GlobalData::g_mChatBubbleColorO;
      b_myNameStr = GlobalData::g_my_profile.name_str;
      b_avatarPathStr = GlobalData::g_my_profile.avatar_str;
      emit globalDataChanged();
    }
}

void ThreadInfo::checkNetConnection()
{
//  qDebug()<<"invoke: void NetManager::refreshLocalHostIP()";
}

