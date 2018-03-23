#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include "GlobalData.h"
#include "UsrData.h"
#include "HiveDoubleBuffer.h"

#include "../libs/libParsley/src/PLoop.h"

#include <QThread>
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
#include <QTimer>
#include <QUuid>

#include <unordered_map>
#include <forward_list>
#include <mutex>

class AppDataManager;

class AppDataManager final
    : public QThread
{
  Q_OBJECT

public:
  explicit AppDataManager(QObject *parent = 0);
  ~AppDataManager();

  void stop();

  static bool pushInboundBuffer(NetPacket *packet);
  static bool pushOutboundBuffer(NetPacket *packet);

public slots:
  void onUsrEntered(const UsrProfileStruct &usrProfileStruct);
  void onUsrLeft(QString *usrKey);
  void onMessageCome(const Message::TextMessage &messageStruct, bool fromMe);
  void onUpdatesAvailable();

protected:
  void run();

private:
  Parsley::Loop *loop;

  static HiveDoubleBuffer<NetPacket> inboundNetBuffer;
  static HiveDoubleBuffer<NetPacket> outboundNetBuffer;

  void checkSettings();

  /*!
   * Functions called by constructor AppDataManager::AppDataManager(), only called once when during initialization.
   */
  inline void initVariable();
  inline void readSettings();
  inline void loadUsrList();
  inline void loadFonts();
  inline void loadUpdates();
  inline void loadTimerTasks();

  inline bool touchFile(const char *path);
  inline bool touchDir(const char *dir);
  inline QString makeUuid();
  inline QJsonDocument makeDefaultSettings();
  inline QJsonDocument makeUpdateJson(const int version[]);

  inline void updateUsr(const UsrProfileStruct &usrProfileStruct);
  inline void deleteUsr(const QStringList usrInfoStrList);

  /*!
   * Maps for storing settings
   */
  static std::map<QString, int*> settings_int_hash;
  static std::map<QString, QColor*> settings_qcolor_hash;
  static std::map<QString, QString*> settings_qstring_hash;
  static std::map<QString, bool*> settings_bool_hash;

private slots:
  void writeSettings();

signals:
  void updatesAvailable();
  void usrProfileLoaded(UsrData *userData);
  void usrProfileChanged(UsrData *userData);
  void messageLoaded(Message::TextMessage messageStrList, bool fromMe);


};


#endif // DATAMANAGER_H
