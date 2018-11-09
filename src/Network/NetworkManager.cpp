#include "NetworkManager.h"


NetworkManager::NetworkManager(QObject *parent) : QObject(parent)
{
  uv_server = new HiveServer(this);
  uv_server->start();
  checkUpdate();
}

NetworkManager::~NetworkManager()
{
//  udpSendUsrLeave();
  uv_server->stop();
  //!  Wait for timer: Only touch when crash on quit!!!
  if(!uv_server->wait(5000))
    {
      uv_server->terminate();
      uv_server->wait(5000);
      Log::gui(Log::Info, "NetworkManager::~NetworkManager()", "Fail to quit UvServer, destryoing it...");
    }
  Log::gui(Log::Info, "NetworkManager::~NetworkManager()", "Successfully destroyed NetworkManager...");
}

void NetworkManager::checkUpdate()
{
  http_update_manager = new QNetworkAccessManager(this);
  http_update_reply = http_update_manager->head(QNetworkRequest(Global::update_url));
  connect(http_update_reply, &QNetworkReply::finished,
          this, &NetworkManager::onRedirectFinished);
}

void NetworkManager::udpProcessUsrLeft(QString *usrKey)
{
  if(*usrKey == Global::settings.profile_uuid_str)
    {
      emit usrLeft(usrKey);
      Log::net(Log::Warning, "NetworkManager::udpProcessUsrLeft()", "Myself left.");
      return;
    }
  Log::net(Log::Warning, "NetworkManager::udpProcessUsrLeft()", "Someone left.");
  emit usrLeft(usrKey);
}

void NetworkManager::udpProcessFileTran(const Message::TextMessage &fileInfoStruct)
{
//  file_info_struct.index = json_obj.value("index");
//  file_info_struct.name = json_obj.value("name").toString();
//  file_info_struct.size = json_obj.value("size").toInt();
//  file_info_struct.type = (GUI::BuiltInIconType)json_obj.value("type").toInt();
}

void NetworkManager::udpSendMessage(const QJsonObject &msg)
{
  uv_server->sendTextMessage(msg);
}

void NetworkManager::onRedirectFinished()
{
  if(http_update_reply->error() != QNetworkReply::NoError)
    {
      Log::net(Log::Warning, "NetworkManager::onRedirectFinished()", QString(http_update_reply->error()));
      return;
    }
  QUrl redirectUrl = QString(http_update_reply->rawHeader("Location"));
  Log::net(Log::Warning, "NetworkManager::onRedirectFinished()", redirectUrl.toString());

  http_update_manager->deleteLater();
  http_update_reply->deleteLater();
  http_update_manager = new QNetworkAccessManager(this);
  http_update_reply = http_update_manager->get(QNetworkRequest(redirectUrl));

  connect(http_update_reply, &QNetworkReply::readyRead,
          [this]() {
            http_update_file.append(http_update_reply->readAll());
          });
  connect(http_update_reply, &QNetworkReply::finished,
          [this]() {
            QJsonParseError err;
            QJsonDocument doc = QJsonDocument::fromJson(http_update_file, &err);
            if(err.error == QJsonParseError::NoError)
              {
                if(doc.isObject())
                  {
                    QJsonObject json_obj = doc.object();
                    Global::update_struct.version[0] = json_obj.value("stable_version").toInt();
                    Global::update_struct.version[1] = json_obj.value("beta_version").toInt();
                    Global::update_struct.version[2] = json_obj.value("alpha_version").toInt();
                    Global::update_struct.message = json_obj.value("message").toString();
                    Global::update_struct.title = json_obj.value("title").toString();
                    if(Global::versionCompare(Global::update_struct.version, Global::current_version))
                      {
                        Log::net(Log::Info, "NetworkManager::onRedirectFinished()", "update available");
                        emit updateAvailable();
                      }
                    else
                      {
                        Log::net(Log::Info, "NetworkManager::onRedirectFinished()", "version already new");
                      }
                  }
                else
                  {
                    Log::net(Log::Critical, "NetworkManager::onRedirectFinished()", "Update Json Document is not a valid JSON object.");
                  }
              }
            else
              {
                Log::net(Log::Critical, "NetworkManager::onRedirectFinished()", err.errorString());
              }
            qDebug()<<"@NetworkManager: Got update file: "<<http_update_file;
            http_update_manager->deleteLater();
            http_update_reply->deleteLater();
          });
}





