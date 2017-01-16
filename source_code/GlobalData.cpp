#include "GlobalData.h"


///UI
int GlobalData::window_defaultWidth = 900;
int GlobalData::window_defaultHeight = 600;

QFont GlobalData::font_main;
QFont GlobalData::font_chatTextEditor;
QFont GlobalData::font_chatBubble;
QFont GlobalData::font_combWidgetUsrName;
QFont GlobalData::font_combWidgetIpAddr;
QFont GlobalData::font_menuButton;
QFont GlobalData::font_scrollStackTitle;
QFont GlobalData::font_scrollStackSubtitle;

QColor GlobalData::color_darkGrey = QColor(100,100,100);
QColor GlobalData::color_lightGrey = QColor(225,225,225);
QColor GlobalData::color_brown = QColor(103,72,0);
QColor GlobalData::color_hiveYellow = QColor(255,181,0);
QColor GlobalData::color_lightYellow = QColor(255,215,126);

QColor GlobalData::color_window = QColor(255,255,255);
QColor GlobalData::color_alphaTab = QColor(255,255,255,230);
QColor GlobalData::color_tab = QColor(0,0,0,0);

QColor GlobalData::color_defaultChatBubbleI = GlobalData::color_lightYellow;
QColor GlobalData::color_defaultChatBubbleO = GlobalData::color_lightGrey;

QPalette GlobalData::palette_bkg_normalWhite;
QPalette GlobalData::palette_bkg_transparent;
QPalette GlobalData::palette_txt_brown;


///data
int GlobalData::current_version[3] = {0, 0, 7};
Settings::SettingsStruct GlobalData::settings_struct;
UpdateStruct GlobalData::update_struct;
QUrl GlobalData::update_url = QUrl("http://updates.hivechat.org");
QUrl GlobalData::download_url = QUrl("http://download.hivechat.org");

QHash<QString, UsrProfileStruct> GlobalData::saved_usr_profile_hash;
QHash<QString, UsrData*> GlobalData::online_usr_data_hash;//used

///netr
QString GlobalData::g_localHostIP;

QString GlobalData::getCurrentTime()
{
  return QDateTime::currentDateTime().toString("yyyy_MM_dd_hh_mm_ss");
}

QString GlobalData::getRandomString(const int &digit)
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

bool GlobalData::versionCompare(const int (&old)[3], const int (&fresh)[3])
{
  //return true if fresh is really fresh
  if(fresh[0] != old[0]
     || fresh[1] != old[1]
     || fresh[2] != old[2])
    {
      if(fresh[0] > old[0])
        {
          return true;
        }
      else
        {
          if(fresh[1] > old[1])
            {
              return true;
            }
          else
            {
              if(fresh[2] > old[2])
                {
                  return true;
                }
              else
                {
                  return false;
                }
            }
        }
    }
  else
    {
      return false;
    }
}

void GlobalData::TEST_printUsrProfileStruct(const UsrProfileStruct &usrProfileStruct, const QString &str)
{
  qDebug()<<endl<<"Test by "<<str;
  qDebug()<<usrProfileStruct.key;
  qDebug()<<usrProfileStruct.name;
  qDebug()<<usrProfileStruct.ip;
  qDebug()<<usrProfileStruct.avatar<<endl;
}


