#ifndef CentralWidget_H
#define CentralWidget_H

#include <QVBoxLayout>
#include <QHBoxLayout>

#include <QFile>
#include <QDir>
#include <QUdpSocket>

#include <QListWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QTextBrowser>

class CentralWidget : public QWidget
{
  Q_OBJECT

public:
  CentralWidget(QWidget *parent = 0);
  ~CentralWidget();




public:
  QHBoxLayout *main_layout;
    QVBoxLayout *side_layout;
      QLineEdit *search_lineedit;
      QHBoxLayout *comb_edit_layout;
        QPushButton *search_button;
        QPushButton *add_comb_button;
        QPushButton *del_comb_button;
      QListWidget *honeycomb_listwidget;
        QListWidgetItem *honeycomb_item;
    QVBoxLayout *message_layout;
      QUdpSocket *UDPSocket;
      QTextBrowser *message_browser;
      QHBoxLayout *send_msg_layout;
        QTextEdit *send_msg_textedit;
        QPushButton *send_msg_button;

  QString read_file(QString, QString);
  void write_file(QString);

private slots:
  void add_new_comb();
  void del_old_comb();
  void import_comb();
  void on_message_browser_highlighted();
  void UDP_broadcast();

};


#endif // CentralWidget_H
