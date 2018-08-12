#include "GlobalData.h"


///UI
int Global::window_dpr;
int Global::window_defaultWidth = 900;
int Global::window_defaultHeight = 600;

QFont Global::font_main;
QFont Global::font_chatTextEditor;
QFont Global::font_chatBubble;
QFont Global::font_combWidgetUsrName;
QFont Global::font_combWidgetIpAddr;
QFont Global::font_menuButton;
QFont Global::font_scrollStackTitle;
QFont Global::font_scrollStackSubtitle;

QColor Global::color_darkGrey = QColor(100,100,100);
QColor Global::color_lightGrey = QColor(225,225,225);
QColor Global::color_brown = QColor(103,72,0);
QColor Global::color_hiveYellow = QColor(255,181,0);
QColor Global::color_lightYellow = QColor(255,215,126);

QColor Global::color_window = QColor(255,255,255);
QColor Global::color_alphaTab = QColor(255,255,255,230);
QColor Global::color_tab = QColor(0,0,0,0);

QColor Global::color_defaultChatBubbleI = Global::color_lightYellow;
QColor Global::color_defaultChatBubbleO = Global::color_lightGrey;

QPalette Global::palette_bkg_normalWhite;
QPalette Global::palette_bkg_transparent;
QPalette Global::palette_txt_brown;


///data
int Global::current_version[3] = {0, 0, 8};
Settings::SettingsStruct Global::settings;
UpdateStruct Global::update_struct;
QUrl Global::update_url = QUrl("http://updatestest.hivechat.org");
QUrl Global::download_url = QUrl("http://download.hivechat.org");

//QHash<QString, UsrData*> Global::offline_usr_data_hash;
//QHash<QString, UsrData*> Global::online_usr_data_hash;//used
QMultiHash<QString, QPair<int, int> > Global::file_tran_progress_hash;//used

QList<QJsonObject> Global::message_queue;

#ifndef Q_OS_WIN
const std::string Global::data_location_dir = QStandardPaths::writableLocation(QStandardPaths::DataLocation).toStdString() + "/Hive!";
#else
const QString GlobalData::data_location_dir = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
#endif
const std::string  Global::user_data_dir = Global::data_location_dir + "/usr";
const std::string  Global::log_dir = Global::data_location_dir + "/log";

const std::string  Global::contacts_file_dir = Global::data_location_dir + "/contacts.json";
const std::string  Global::settings_file_dir = Global::data_location_dir + "/settings.json";
const std::string  Global::update_file_dir = Global::data_location_dir + "/update.json";


///netr
QString Global::g_localHostIP = "Offline";

QString Global::getCurrentTime()
{
  return QDateTime::currentDateTime().toString("yyyy_MM_dd_hh_mm_ss");
}

QString Global::getRandomString(const int &digit)
{
  const char alphabet_char[64] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_";
  qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
  QString random_str;
  for(int i = 0; i < digit; i ++)
    {
      random_str.append(alphabet_char[qrand()%63]);
    }

  return random_str;
}

bool Global::versionCompare(const int (&fresh)[3], const int (&old)[3])
{
  //return true if fresh is really fresh
  if(fresh[0] > old[0])
    {
      return true;
    }
  else if(fresh[1] > old[1])
    {
      return true;
    }
  else if(fresh[2] > old[2])
    {
      return true;
    }
  else
    {
      return false;
    }
}

void Global::TEST_printUsrProfile(const UsrProfile &p, const QString &str)
{
  qDebug()<<endl<<"Test by "<<str;
  qDebug()<<p.key;
  qDebug()<<p.name;
  qDebug()<<p.ip;
  qDebug()<<p.online;
  qDebug()<<p.avatar<<endl;
}


