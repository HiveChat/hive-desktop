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
  int r = file_.open(O_WRONLY | O_CREAT, 0664, Agio::Sync);
  if(r == 0)
    opened_ = true;
  Agio::Buffer* data = file_.readAll();
  QJsonParseError err;
  json_ = QJsonDocument::fromJson(QByteArray(data->data(), data->size()), &err);
  if(err.error != QJsonParseError::NoError || json_.isNull())
    {
      file_.truncate(0, Agio::Sync);
      file_.write("", Agio::Sync);
    }
  return r;
}

int Database::write()
{
  if(path_ == "")
    return -1;
  if(opened_)
    return -1;
  std::string data(json_.toJson(QJsonDocument::Indented).data());
  return file_.write(data, Agio::Sync);
}

int Database::close()
{
  return file_.close(Agio::Sync);
}




Map::Map()
  : Database()
{
}

Map::Map(const std::string& path)
  : Database(path)
{
  open();
  importJson();
}

Map::~Map()
{

}

QJsonValue Map::value(const QString& key)
{
  return map_.value(key);
}

void Map::insert(const QString& key, const QJsonValue& val)
{
  map_.insert(key, val);
  exportJson();
  write();
}

void Map::remove(const QString& key)
{
  map_.remove(key);
  exportJson();
  write();
}

void Map::exportJson()
{
  QJsonObject obj;
  for(auto key : map_.keys())
    obj.insert(key, map_.value(key));
  json_.setObject(obj);
}

void Map::importJson()
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
  importJson();
}

Array::~Array()
{

}

void Array::importJson()
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

void ShardedArray::importJson()
{

}
