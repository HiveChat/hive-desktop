#include "TcpServer.h"


TcpRunnable::TcpRunnable(QTcpSocket *tcpSocket, const Task &task, const QByteArray &data)
  : tcp_socket(tcpSocket)
  , tcp_task(task)
  , buffer(data)
{
}

void TcpRunnable::run()
{
  switch (tcp_task) {
    case Read:
      {

        break;
      }
    case Write:
      {
        if(tcp_socket->state() == QTcpSocket::ConnectedState)
          {
            tcp_socket->write(buffer);
            tcp_socket->flush();
            tcp_socket->waitForBytesWritten(100);
            qDebug().noquote()<<"Socket:"<<tcp_socket->socketDescriptor()<< "done!";
          }

        break;
      }
    default:
      {

        break;
      }
    }


}



TcpServer::TcpServer()
{


//  thread_pool = new QThreadPool(this);
//  thread_pool->setMaxThreadCount(10);
//  this->listen(QHostAddress::Any, 23233);

//  connectToPeer(".");

}

TcpServer::~TcpServer()
{
  delete boost_tcp_server;
}

int64_t counter = 0;
void wait_for_a_while(uv_idle_t* handle) {
  sleep(1);
    counter++;

    if (counter >= 3)
        uv_idle_stop(handle);
}


void TcpServer::start()
{
  uv_idle_t idler;

  uv_idle_init(uv_default_loop(), &idler);
  uv_idle_start(&idler, wait_for_a_while);

  printf("Idling...\n");
  uv_run(uv_default_loop(), UV_RUN_DEFAULT);

  uv_loop_close(uv_default_loop());
//  qDebug()<<this->thread();
//  boost::asio::io_service io_service;
//  BoostTcpServer boostTcpServer(io_service);
//  io_service.run();
}

bool TcpServer::connectToPeer(const QString &usrKey)
{
  QTcpSocket *tcpSocket = new QTcpSocket();
  tcpSocket->connectToHost(QHostAddress("192.168.21.100"), 23233);
  connect(tcpSocket, SIGNAL(connected()), tcpSocket, SLOT(write("helloTim")));
}

void TcpServer::incomingConnection(qintptr handle)
{
  qDebug()<<handle;

//  if(tcp_socket_hash.contains(handle))
//    {
//      TcpRunnable *run = new TcpRunnable(tcp_socket_hash.value(handle));
//      run->setAutoDelete(true);
//      thread_pool->start(run);
//    }
//  else
//    {
//      QTcpSocket *tcpSocket = new QTcpSocket();
//      tcp_socket_hash.insert(handle, tcpSocket);
//      connect(tcpSocket, &QTcpSocket::readyRead, this, &TcpServer::readData);
//      connect(tcpSocket, &QTcpSocket::disconnected, [this]() {
//          qDebug()<<"disconnected";
//        });
//      connect(tcpSocket, &QTcpSocket::destroyed, [this]() {
//                qDebug()<<"destroyed";
//              });
//      tcpSocket->setSocketDescriptor(handle);

//      TcpRunnable *run = new TcpRunnable(tcpSocket);
//      run->setAutoDelete(true);
//      thread_pool->start(run);
//    }
}

void TcpServer::readData()
{
  qDebug()<<tcp_socket_hash.values().first()->readAll();
}



using boost::asio::ip::tcp;

std::string make_daytime_string()
{
  using namespace std; // For time_t, time and ctime;
  time_t now = time(0);
  return ctime(&now);
}

//int main()
//{
//  try
//  {
//    boost::asio::io_service io_service;
//    tcp_server server(io_service);
//    io_service.run();
//  }
//  catch (std::exception& e)
//  {
//    std::cerr << e.what() << std::endl;
//  }

//  return 0;
//}

boost::shared_ptr<BoostTcpConnection> BoostTcpConnection::create(boost::asio::io_service &io_service)
{
  return boost::shared_ptr<BoostTcpConnection>(new BoostTcpConnection(io_service));
}

tcp::socket &BoostTcpConnection::socket()
{
  return socket_;
}

void BoostTcpConnection::start()
{
  message_ = make_daytime_string();

  boost::asio::async_write(socket_, boost::asio::buffer(message_),
                           boost::bind(&BoostTcpConnection::handle_write, shared_from_this(),
                                       boost::asio::placeholders::error,
                                       boost::asio::placeholders::bytes_transferred));
}

BoostTcpConnection::BoostTcpConnection(boost::asio::io_service &io_service)
  : socket_(io_service)
{
}

void BoostTcpConnection::handle_write(const boost::system::error_code &, size_t)
{
}




BoostTcpServer::BoostTcpServer(boost::asio::io_service &io_service)
  : acceptor_(io_service, tcp::endpoint(tcp::v4(), 23232))
{
  start_accept();
}

void BoostTcpServer::start_accept()
{
  boost::shared_ptr<BoostTcpConnection> newConnection = BoostTcpConnection::create(acceptor_.get_io_service());

  acceptor_.async_accept(newConnection->socket(),
                         boost::bind(&BoostTcpServer::handle_accept, this, newConnection, boost::asio::placeholders::error));
}

void BoostTcpServer::handle_accept(boost::shared_ptr<BoostTcpConnection> newConnection, const boost::system::error_code &error)
{
  if (!error)
    {
      newConnection->start();
    }

  start_accept();
}
