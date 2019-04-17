#include "Database.h"

#include <QJsonObject>


using namespace DB;

Database::Database(const std::string &path)
  : path_(path)
{
}

int Database::open()
{
  if(opened_)
    return -1;
  file_.setPath(path_);
  int r = file_.open(O_WRONLY | O_CREAT, 0664, Parsley::Sync);
  if(r == 0)
    opened_ = true;
  std::string data = file_.readAll();
  QJsonParseError err;
  json_ = QJsonDocument::fromJson(QByteArray(data.data(), data.size()), &err);
  if(err.error != QJsonParseError::NoError || json_.isNull())
    {
      file_.truncate(0, Parsley::Sync);
      file_.write("", Parsley::Sync);
    }
  return r;
}

int Database::close()
{
  return file_.close(Parsley::Sync);
}

Map::Map()
{

}

Array::Array()
{

}

ShardedArray::ShardedArray()
{

}
