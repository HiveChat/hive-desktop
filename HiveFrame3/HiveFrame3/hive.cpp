#include "hive.h"


HiveApp::HiveApp(int &argc, char **argv)
  : QApplication(argc, argv)
{
#ifdef Q_OS_OSX
  QApplication::setQuitOnLastWindowClosed(false);
  QtMac::setBadgeLabelText("Hi");
#endif

  thread_net = new QThread(this);
  data_manager = new AppDataManager();
  data_manager->moveToThread(thread_net);




#ifdef Q_OS_OSX
  QtMac::setBadgeLabelText("");
#endif
}

bool HiveApp::event(QEvent *event)
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
