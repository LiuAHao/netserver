#pragma once
#include"TcpServer.h"
#include"EventLoop.h"
#include"Connection.h"
#include"ThreadPool.h"

//回显服务器

class EchoServer
{
private:
    TcpServer tcpserver_;
    ThreadPool threadpool_;     //处理业务的工作线程池
public:
    EchoServer(const std::string &ip,const uint16_t port,int subthreadnum = 3,int workthreadnum = 5);
    ~EchoServer();
    void Start();

    void HandleNewConnection(Connection* conn);             //用于处理新客户端的请求
    void HandleClose(Connection* conn);             //关闭客户端的连接，在TcpServer类中回调此函数
    void HandleError(Connection* conn);             //客户端的错误连接，在TcpServer类中回调此函数
    void HandleMessage(Connection* conn,std::string message); //处理客户端的请求报文，在TcpServer中回调此函数
    void HandleSendComplete(Connection* conn);                //数据传送完毕后，在TcpServer类中回调此函数      
    //void HandleEpollTimeOut(EventLoop* loop);                //epoll_wait()超时，在TcpServer类中回调此函数    
    void OnMessage(Connection* conn,std::string message);        //处理客户端的请求报文，增加到线程池中
};