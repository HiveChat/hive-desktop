#include "CentralWidget.h"
#include <QDebug>


CentralWidget::CentralWidget(QWidget *parent) : QWidget(parent)
{
  ////////layout
  main_layout         = new QHBoxLayout(this);
  comb_edit_layout    = new QHBoxLayout();
  side_layout         = new QVBoxLayout();
  message_layout      = new QVBoxLayout();
  send_msg_layout     = new QHBoxLayout();

  ////////widget
  search_lineedit     = new QLineEdit();
  honeycomb_listwidget= new QListWidget();
  QValidator *search_lineedit_validator = new QIntValidator(0,65535,this);
  search_lineedit->setValidator(search_lineedit_validator);
  search_lineedit->setPlaceholderText("honeycomb# here!  0~65535");

  search_button       = new QPushButton("Search");
  add_comb_button     = new QPushButton("+");
  del_comb_button     = new QPushButton("-");
  //connect(search_button, SIGNAL(clicked()),this,SLOT(import_comb()));
  connect(add_comb_button, SIGNAL(clicked()), this, SLOT(add_new_comb()));
  connect(del_comb_button, SIGNAL(clicked()), this, SLOT(del_old_comb()));

  message_browser     = new QTextBrowser();
  send_msg_textedit   = new QTextEdit();
  send_msg_button     = new QPushButton("Send");

  send_msg_textedit->setPlaceholderText("say something...");
  send_msg_textedit->setFixedHeight(65);
  send_msg_button->setFixedHeight(76);
  connect(send_msg_button, SIGNAL(clicked()), this, SLOT(UDP_broadcast()));
  connect(honeycomb_listwidget, SIGNAL(currentRowChanged(int)), this, SLOT(on_message_browser_highlighted()));


  comb_edit_layout->setSpacing(0);
  comb_edit_layout->addWidget(search_button);
  comb_edit_layout->addWidget(add_comb_button);
  comb_edit_layout->addWidget(del_comb_button);

  send_msg_layout->setSpacing(0);
  send_msg_layout->addWidget(send_msg_textedit);
  send_msg_layout->addWidget(send_msg_button);

  //side_layout->setSpacing(0);
  side_layout->addWidget(search_lineedit);
  side_layout->addLayout(comb_edit_layout);
  side_layout->addWidget(honeycomb_listwidget);

  message_layout->addWidget(message_browser);
  message_layout->addLayout(send_msg_layout);

  main_layout->addLayout(side_layout);
  main_layout->addLayout(message_layout);

  import_comb();


}

CentralWidget::~CentralWidget()
{
  deleteLater();
}

void write_file(QString Filename, QString Content)
{
    QFile mfile(Filename);

    if(!mfile.open(QFile::WriteOnly | QFile::Text))
    {
        qDebug()<<"God Bless The TempFile! err in writting!";
        return;
    }

    QTextStream out(&mfile);
    out<<Content;
    mfile.flush();
    mfile.close();
}

QString read_file(QString Filename)
{
    QFile mfile(Filename);

    if(!mfile.open(QFile::ReadOnly | QFile::Text))
    {
        qDebug()<<"God Bless The TempFile! err in reading!"+Filename;
        return "ERR READING FILE";
    }

    QTextStream in(&mfile);
    QString textt = in.readAll();



    //mfile.flush();
    mfile.close();

    return textt;
}


////////slots
void CentralWidget::add_new_comb()
{
  //add QListWidgetItem
  //QString comb_num_qstr = search_lineedit->text();
  honeycomb_item      = new QListWidgetItem(search_lineedit->text());
  honeycomb_listwidget->addItem(honeycomb_item);

  //add temp file
  ::write_file("/Applications/Hive/"+search_lineedit->text(), "<b>Honeycomb# "+search_lineedit->text()+"</b>");
  message_browser->setText(::read_file("/Applications/Hive/"+search_lineedit->text()));
  //add socket
  UDPSocket = new QUdpSocket(this);
  UDPSocket->bind(65535, QUdpSocket::ShareAddress);

}

void CentralWidget::del_old_comb()
{
  if(honeycomb_listwidget->currentItem() != NULL)
    {
      qDebug()<<QFile::remove("/Applications/Hive/"+honeycomb_listwidget->currentItem()->text());

      QListWidgetItem *item = honeycomb_listwidget->takeItem(honeycomb_listwidget->currentRow());
      delete item;
    }
}

void CentralWidget::import_comb()
{
  QDir comb_file_dir("/Applications/Hive/");
  foreach (QFileInfo comb_file_info, comb_file_dir.entryInfoList())
    {
      if(comb_file_info.fileName() != ".." && comb_file_info.fileName() != ".")
        {
          honeycomb_item      = new QListWidgetItem(comb_file_info.fileName());
          honeycomb_listwidget->addItem(honeycomb_item);
          qDebug()<<comb_file_info.fileName();
        }
    }
}

void CentralWidget::on_message_browser_highlighted()
{
  qDebug()<<"get it";
  QString s= "Hive! - #"+honeycomb_listwidget->currentItem()->text();
  //setWindowTitle(s);
  //qDebug()<<"get it2";
  message_browser->setText(::read_file("/Application/Hive/"+honeycomb_listwidget->currentItem()->text()));
}

void CentralWidget::UDP_broadcast()
{
  QByteArray datagram = send_msg_textedit->toPlainText().toUtf8();
  UDPSocket->writeDatagram(datagram.data(), datagram.size(), QHostAddress::Broadcast,honeycomb_listwidget->currentItem()->text().toInt());
}
