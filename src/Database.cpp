#include "Database.h"

using namespace DB;

Database::Database(const std::string &path)
  : path_(path)
{
}

int Database::open()
{
  file_.setPath(path_);
  int r = file_.open(O_WRONLY | O_CREAT, 0664, Parsley::Sync);
  if(r == 0)
    opened_ = true;
  //! TODO
  //!
  return r;
}

int Database::close()
{
  return file_.close(Parsley::Sync);
}

Map::Map() {}

Array::Array() {}

ShardedArray::ShardedArray() {}
