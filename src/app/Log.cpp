#include "Log.h"

void Log::gui(const Level &level, const QString &function, const QString &str)
{
  switch (level) {
    case Level::Info:
      {
        qInfo().noquote()<<QTime::currentTime().toString() << " GUI_NORM "<< function << str;
        break;
      }
    case Level::Warning:
      {
        qWarning().noquote()<<QTime::currentTime().toString() << " GUI_ERRO " << function << str;
        break;
      }
    case Level::Critical:
      {
        qCritical().noquote()<<QTime::currentTime().toString() << " GUI_CRIT " << function << str;
      }

    default:
      break;
    }
}

void Log::net(const Log::Level &level, const QString &function, const QString &str)
{
  switch (level) {
    case Level::Info:
      {
        qInfo().noquote()<<QTime::currentTime().toString() << " NET_NORM "<< function << str;
        break;
      }
    case Level::Warning:
      {
        qWarning().noquote()<<QTime::currentTime().toString() << " NET_ERRO " << function << str;
        break;
      }
    case Level::Critical:
      {
        qCritical().noquote()<<QTime::currentTime().toString() << " NET_CRIT " << function << str;
      }

    default:
      break;
    }
}

void Log::dat(const Log::Level &level, const QString &function, const QString &str)
{
  switch (level) {
    case Level::Info:
      {
        qInfo().noquote()<<QTime::currentTime().toString() << " DAT_NORM "<< function << str;
        break;
      }
    case Level::Warning:
      {
        qWarning().noquote()<<QTime::currentTime().toString() << " DAT_ERRO " << function << str;
        break;
      }
    case Level::Critical:
      {
        qCritical().noquote()<<QTime::currentTime().toString() << " DAT_CRIT " << function << str;
      }

    default:
      break;
    }
}
