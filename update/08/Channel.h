#pragma once

#include<sys/epoll.h>
#include<functional>
#include"Epoll.h"
#include"InetAddress.h"
#include"Socket.h"

class Epoll;

class Channel
{
private:
    int fd_;                    //Channel拥有的id，一一对应
    Epoll *ep_ = nullptr;        //Channel对应的红黑树，一一对应
    bool inepoll_ = false;      //标识Channel是否已经添加到epoll中，未添加：调用epoll_ctl时用EPOLL_CTL_ADD，反之用EPOLL_CTL_MOD
    uint32_t events_ = 0;       //fd_需要监视的事件
    uint32_t revents_ = 0;      //fd_已经发生的事件
    std::function<void()> readcallback_;    //fd_读事件的回调函数

public:
    Channel(Epoll* ep,int fd);
    ~Channel();

    int fd();
    void usset();                   //采用边缘触发
    void enablereading();
    void setinepoll();              //epoll_wait()监听fd_的读事件
    void setrevents(uint32_t ev);   //设置revents_成员为ev
    bool inpoll();
    uint32_t events();
    uint32_t revents();

    void handleevent();             //事件处理函数，epoll_wait()返回的时候，执行它

    void newconnection(Socket* servsock);           //用于处理新客户端的请求
    void onmessage();                               //处理对端发送的消息
    void setreadcallback(std::function<void()>fn);  //设置fd_读事件的回调函数
};