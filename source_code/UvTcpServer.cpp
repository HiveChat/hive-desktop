#include "UvTcpServer.h"


int64_t tcpOp::counter = 0;

UvTcpServer::UvTcpServer(QObject *parent) : QThread(parent)
{

}

void UvTcpServer::run()
{
  tcpOp op;


  uv_idle_t idler;

  uv_idle_init(uv_default_loop(), &idler);
  uv_idle_start(&idler, op.wait_for_a_while);

  printf("Idling...\n");
  uv_run(uv_default_loop(), UV_RUN_DEFAULT);

  uv_loop_close(uv_default_loop());
}
