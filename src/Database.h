#ifndef DATABASE_H
#define DATABASE_H

#include <libparsley/file.h>

#include <string>
#include <vector>

#include <QJsonDocument>
#include <QHash>


namespace DB {
class Database;
class Map;
class Array;
class ShardedArray;

class Database
{
public:
  Database();
  Database(const std::string& path);
  virtual ~Database();
  int open();
  int write();
  int close();

protected:
  virtual void importJson() = 0;
  virtual void exportJson() = 0;

  bool opened_ = false;
  std::string path_;
  Parsley::File file_;
  QJsonDocument json_;
};

class Map
    : public Database
{
public:
  Map();
  Map(const std::string& path);
  virtual ~Map();

  QJsonValue value(const QString& key);
  void insert(const QString& key, const QJsonValue& val);
  void remove(const QString& key);

  void exportJson();

protected:
  virtual void importJson();

private:
  QHash<QString, QJsonValue> map_;
};

class Array
    : public Database
{
public:
  Array();
  Array(const std::string& path);
  virtual ~Array();

protected:
  virtual void importJson();

private:
  std::vector<QJsonValue> vector_;
};

class ShardedArray
    :public Database
{
public:
  ShardedArray();
  ShardedArray(const std::string& path);
  virtual ~ShardedArray();

protected:
  virtual void importJson();

};

}



#endif // DATABASE_H
