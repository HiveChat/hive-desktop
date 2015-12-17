#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QDebug>
#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QStandardPaths>

class DataManager : public QObject
{
  Q_OBJECT

public:
  explicit DataManager(QObject *parent = 0);

  void addUsr(QString usrName, QString ipAddr, QString macAddr);
  void deleteUsr(QString usrName, QString ipAddr, QString macAddr);
  void loadUsrForm();
  //void addChatHistory();

signals:

public slots:

private:
  bool checkDir(QString dir);

  QString app_data_local_path = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
  QString usr_path = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation) + "/usr/";
  QString log_path = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation) + "/log/";

  QString usr_list_file_path = app_data_local_path + "/usr_list.json";
};

#endif // DATAMANAGER_H
