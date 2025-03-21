#include"TcpServer.h"

TcpServer::TcpServer(const std::string &ip,const uint16_t port)
{
    acceptor_ = new Acceptor(&loop_,ip,port);
    acceptor_->setnewconnectioncb(std::bind(&TcpServer::newconnection,this,std::placeholders::_1));
}

TcpServer::~TcpServer()
{
    delete acceptor_;
}

void TcpServer::start()
{
    loop_.run();
}

void TcpServer::newconnection(Socket* clientsock)           //用于处理新客户端的请求
{
    Connection* conn = new Connection(&loop_,clientsock);
}