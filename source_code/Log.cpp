#include "Log.h"

void Log::gui(const Level &level, const QString &function, const QString &str)
{
  switch (level) {
    case Level::Normal:
      {
        qDebug().noquote()<<QTime::currentTime().toString() << " GUI "<< function << str;
        break;
      }
    case Level::Error:
      {
        qDebug().noquote()<<QTime::currentTime().toString() << " GUI_ERR " << function << str;
        break;
      }
    case Level::Critical:
      {
        qDebug().noquote()<<QTime::currentTime().toString() << " GUI_CRITICAL_ERR " << function << str;
      }

    default:
      break;
    }
}

void Log::net(const Log::Level &level, const QString &function, const QString &str)
{
  switch (level) {
    case Level::Normal:
      {
        qDebug().noquote()<<QTime::currentTime().toString() << " NET "<< function << str;
        break;
      }
    case Level::Error:
      {
        qDebug().noquote()<<QTime::currentTime().toString() << " NET_ERR " << function << str;
        break;
      }
    case Level::Critical:
      {
        qDebug().noquote()<<QTime::currentTime().toString() << " NET_CRITICAL_ERR " << function << str;
      }

    default:
      break;
    }
}

void Log::dat(const Log::Level &level, const QString &function, const QString &str)
{
  switch (level) {
    case Level::Normal:
      {
        qDebug().noquote()<<QTime::currentTime().toString() << " DAT "<< function << str;
        break;
      }
    case Level::Error:
      {
        qDebug().noquote()<<QTime::currentTime().toString() << " DAT_ERR " << function << str;
        break;
      }
    case Level::Critical:
      {
        qDebug().noquote()<<QTime::currentTime().toString() << " DAT_CRITICAL_ERR " << function << str;
      }

    default:
      break;
    }
}
