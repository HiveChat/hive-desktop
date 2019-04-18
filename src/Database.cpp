#include "Database.h"

#include <QJsonObject>
#include <QJsonArray>
#include <QStringList>

using namespace DB;

Database::Database()
{
}

Database::Database(const std::string &path)
  : path_(path)
{
}

Database::~Database()
{

}

int Database::open()
{
  if(path_ == "")
    return -1;
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
  : Database()
{
}

Map::Map(const std::string& path)
  : Database(path)
{
  open();
  load();
}

Map::~Map()
{

}

void Map::load()
{
  QJsonObject obj = json_.object();
  for(auto key : obj.keys())
    map_.insert(key, obj[key]);
}




Array::Array()
  : Database()
{
}

Array::Array(const std::string& path)
  : Database(path)
{
  open();
  load();
}

Array::~Array()
{

}

void Array::load()
{
  QJsonArray array = json_.array();
  for(auto val : array)
    vector_.push_back(val);
}




ShardedArray::ShardedArray()
  : Database()
{
  open();
}

ShardedArray::ShardedArray(const std::string& path)
  : Database(path)
{

}

ShardedArray::~ShardedArray()
{

}

void ShardedArray::load()
{

}
