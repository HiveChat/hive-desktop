#ifndef SERVER_H
#define SERVER_H

#include <QHash>
#include <QTcpServer>
#include <QTcpSocket>
#include <QRunnable>
#include <QThreadPool>

#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>


#include <ctime>
#include <iostream>
#include <string>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>

#include <uv.h>
#include <stdio.h>


class TcpServer;
class TcpRunnable;

class BoostTcpServer;
class BoostTcpConnection;




class TcpRunnable : public QRunnable
{
  enum Task{
    Read,
    Write
  };

public:
  explicit TcpRunnable(QTcpSocket *tcpSocket, const Task &task, const QByteArray &data);

protected:
  void run();

private:
  Task tcp_task;
  QByteArray buffer;
  QTcpSocket *tcp_socket;

};

class TcpServer : public QTcpServer
{
  Q_OBJECT

public:
  explicit TcpServer();
  ~TcpServer();

  void start();

  bool connectToPeer(const QString &usrKey);

protected:
  void incomingConnection(qintptr handle);

private:
  BoostTcpServer *boost_tcp_server;

  QHash<QString, QTcpSocket *> tcp_socket_hash;
  QHash<QString, qintptr> socket_discriptor_hash;
  QThreadPool *thread_pool;




private slots:
  void readData();

};



using boost::asio::ip::tcp;

class BoostTcpConnection : public boost::enable_shared_from_this<BoostTcpConnection>
{
public:

  static boost::shared_ptr<BoostTcpConnection> create(boost::asio::io_service& io_service);
  tcp::socket& socket();
  void start();

private:
  BoostTcpConnection(boost::asio::io_service& io_service);
  void handle_write(const boost::system::error_code& /*error*/, size_t /*bytes_transferred*/);

  tcp::socket socket_;
  std::string message_;
};


class BoostTcpServer
{
public:
  BoostTcpServer(boost::asio::io_service& io_service);

private:
  void start_accept();
  void handle_accept(boost::shared_ptr<BoostTcpConnection> newConnection, const boost::system::error_code& error);

  tcp::acceptor acceptor_;
};





#endif // SERVER_H
