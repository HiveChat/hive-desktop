#ifndef DATABASE_H
#define DATABASE_H

#include <libparsley/file.h>

#include <string>

namespace DB {

class Database;
class Map;
class Array;
class ShardedArray;

class Database
{
public:
  Database(const std::string& path);
  int open();
  int close();

protected:
  std::string path_;
  Parsley::File file_;
  bool opened_ = false;
};

class Map
{
public:
  Map();


};

class Array
{
public:
  Array();
};

class ShardedArray
{
public:
  ShardedArray();
};

}



#endif // DATABASE_H
