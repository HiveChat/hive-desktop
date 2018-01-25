#ifndef LOG_H
#define LOG_H

#include <QString>
#include <QDebug>
#include <QTime>

namespace Log
{
  enum Level
  {
    Normal = 0,
    Error = 1,
    Critical = 2,

  };

  void gui(const Level &level, const QString &function, const QString &str);
  void net(const Level &level, const QString &function, const QString &str);
  void dat(const Level &level, const QString &function, const QString &str);

}

#endif // LOG_H
