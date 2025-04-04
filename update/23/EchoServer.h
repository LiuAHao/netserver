#pragma once
#include"TcpServer.h"
#include"EventLoop.h"
#include"Connection.h"

//回显服务器

class EchoServer
{
private:
    TcpServer tcpserver_;
public:
    EchoServer(const std::string &ip,const uint16_t port);
    ~EchoServer();
    void Start();

    void HandleNewConnection(Connection* conn);             //用于处理新客户端的请求
    void HandleClose(Connection* conn);             //关闭客户端的连接，在Connection类中回调此函数
    void HandleError(Connection* conn);             //客户端的错误连接，在Connection类中回调此函数
    void HandleMessage(Connection* conn,std::string message); //处理客户端的请求报文，在Connection中回调此函数
    void HandleSendComplete(Connection* conn);                //数据传送完毕后，在Connection类中回调此函数      
    //void HandleEpollTimeOut(EventLoop* loop);                //epoll_wait()超时，在EventLoop类中回调此函数      
};