#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include "GlobalData.h"
#include "UsrData.h"

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
  static bool checkDir(const QString &directory);

  inline QString makeUuid();
  inline QJsonDocument makeDefaultSettigns();
  inline QJsonDocument makeUpdateJson(const int stable[]);

  inline void initVariable();
  inline void checkFiles();
  inline void loadDefaultGlobalData();
  inline void loadMySettings();
  inline void loadUsrList();
  inline void loadFonts();
  inline void loadUpdates();
  inline void loadTimerTasks();

  inline void updateUsr(const UsrProfileStruct &usrProfileStruct);
  inline void deleteUsr(const QStringList usrInfoStrList);

  //config map
  QHash<QString, int*> settings_hash_int;
  QHash<QString, QColor*> settings_hash_qcolor;
  QHash<QString, QString*> settings_hash_qstring;
  QHash<QString, bool*> settings_hash_bool;

public slots:
  void onUsrEntered(const UsrProfileStruct &usrProfileStruct);
  void onUsrLeft(QString *usrKey);
  void onMessageCome(const Message::TextMessage &messageStruct, bool fromMe);
  void onUpdatesAvailable();

private slots:
  void writeCurrentConfig();

signals:
  void updatesAvailable();
  void usrProfileLoaded(UsrData *userData);
  void usrProfileChanged(UsrData *userData);
  void messageLoaded(Message::TextMessage messageStrList, bool fromMe);


};

#endif // DATAMANAGER_H
