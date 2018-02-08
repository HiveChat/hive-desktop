#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include "GlobalData.h"
#include "UsrData.h"
#include "unordered_map"

#include <QThread>
#include <QMutex>
#include <QDebug>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QFileInfo>
#include <QStandardPaths>

#include <QFontDatabase>
#include <QHostInfo>
#include <QTime>
#include <QTimer>
#include <QUuid>

class AppDataManager : public QObject
{
  Q_OBJECT

public:
  explicit AppDataManager(QObject *parent = 0);
  ~AppDataManager();


private:

  void checkSettings();
  inline bool checkDir(const QString &directory);

  /*!
   * Functions called by constructor AppDataManager::AppDataManager(), only called once when during initialization.
   */
  inline void initVariable();
  inline void checkFiles();
  inline void readSettings();
  inline void loadUsrList();
  inline void loadFonts();
  inline void loadUpdates();
  inline void loadTimerTasks();

  inline QString makeUuid();
  inline QJsonDocument makeDefaultSettings();
  inline QJsonDocument makeUpdateJson(const int stable[]);

  inline void updateUsr(const UsrProfileStruct &usrProfileStruct);
  inline void deleteUsr(const QStringList usrInfoStrList);

  /*!
   * Hashes for storing settings
   */

  std::map<QString, int*> settings_int_hash;
  std::map<QString, QColor*> settings_qcolor_hash;
  std::map<QString, QString*> settings_qstring_hash;
  std::map<QString, bool*> settings_bool_hash;

public slots:
  void onUsrEntered(const UsrProfileStruct &usrProfileStruct);
  void onUsrLeft(QString *usrKey);
  void onMessageCome(const Message::TextMessage &messageStruct, bool fromMe);
  void onUpdatesAvailable();

private slots:
  void writeSettings();

signals:
  void updatesAvailable();
  void usrProfileLoaded(UsrData *userData);
  void usrProfileChanged(UsrData *userData);
  void messageLoaded(Message::TextMessage messageStrList, bool fromMe);


};

#endif // DATAMANAGER_H
