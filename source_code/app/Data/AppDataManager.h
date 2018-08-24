#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include "Global.h"
#include "UsrData.h"
#include "HiveDoubleBuffer.h"

#include "../libs/libParsley/src/PFile.h"
#include "../libs/libParsley/src/PTimer.h"
#include "../libs/libParsley/src/PAsync.h"

#include <unordered_map>

#include <QThread>
#include <QDebug>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QStandardPaths>

#include <QFontDatabase>
#include <QHostInfo>
#include <QTimer>
#include <QUuid>

#include <functional>
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

  static void pushInboundBuffer(NetPacket *packet);
  static void pushOutboundBuffer(NetPacket *packet);

  static bool isUsrNew(const QString &uuid);

  static QHash<QString, UsrData*> usr_data_hash;

public slots:
  void onUsrEntered(UsrProfile &usrProfile);
  void onUsrLeft(QString *usrKey);
  void onMessageCome(const Message::TextMessage &m, bool fromMe);
  void onUpdatesAvailable();

protected:
  void run();

private:
  bool inboundNetBufferReading = false;
  Parsley::Loop *loop;

  static DoubleBuffer<NetPacket*> inboundNetBuffer;
  static DoubleBuffer<NetPacket*> outboundNetBuffer;

  Parsley::Async *read_inbound_async;
  void wakeLoop(DoubleBuffer<NetPacket *> *buf);
  void readInboundNetBuffer();
  void checkSettings(Parsley::Timer *);


  /*!
   * Functions called by constructor AppDataManager::AppDataManager(),
   * only called once when during initialization.
   */
  inline void initVariable();
  inline void loadSettings();
  inline void loadUsrList();
  inline void loadUpdates();

  inline bool touchFile(const std::string &path);
  inline bool touchDir(const std::string &dir);
  inline QString makeUuid();
  inline QJsonDocument makeDefaultSettings();
  inline QJsonDocument makeUpdateJson(const int version[]);

  inline void updateUsr(const UsrProfile &p);
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
