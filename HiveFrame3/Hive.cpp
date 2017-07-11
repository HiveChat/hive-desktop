#include "hive.h"


Hive::Hive(int &argc, char **argv)
  : QApplication(argc, argv)
  , central_widget(new _Showcase())
{
#ifdef Q_OS_OSX
  QApplication::setQuitOnLastWindowClosed(false);
  QtMac::setBadgeLabelText("Hi");
#endif

//  thread_data = new QThread(this);
//  data_manager = new AppDataManager();
//  data_manager->moveToThread(thread_data);




#ifdef Q_OS_OSX
  QtMac::setBadgeLabelText("");
#endif
}

Hive::~Hive()
{
  Log::gui(Log::Normal, "Hive::~Hive()", "Destroying App");
  central_widget->deleteLater();
#ifdef Q_OS_OSX
  QtMac::setBadgeLabelText("Bye");
#endif

//  thread_data->quit();

//  if(!thread_data->wait(500))
//    {
//      Log::gui(Log::Error, "Hive::~Hive()", "Data thread is terminated due to timeout.");
//      thread_data->terminate();
//      thread_data->wait();
//    }


  Log::gui(Log::Normal, "Hive::~Hive()", "Destroyed App");

}

bool Hive::event(QEvent *event)
{
  switch (event->type()) {
    case QEvent::ApplicationActivate:
      {
        //show application when dock icon is clicked.
//        gui_central_widget->showNormal();

        return true;
      }
#ifdef Q_OS_OSX
    case QEvent::FileOpen:
      {
        QFileOpenEvent *openEvent = static_cast<QFileOpenEvent *>(event);

        Log::gui(Log::Normal, "HiveApp::event()", openEvent->file());
        return true;
      }
#endif
    default:
      {
        break;
      }
  }

  return QApplication::event(event);
}
