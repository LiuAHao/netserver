#include"Epoll.h"

Epoll::Epoll()
{
    if((epollfd_ = epoll_create(1)) == -1){
        printf("epollfd_create() failed(%d).\n",errno);
        exit(-1);
    }
}

Epoll::~Epoll()
{
    close(epollfd_);
}

int Epoll::fd()
{
    return epollfd_;
}

void Epoll::updatechannel(Channel* ch)
{
    epoll_event ev;
    ev.data.ptr = ch;
    ev.events = ch->events();
    if(ch->inpoll())    //已经在树上
    {
        if(epoll_ctl(fd(),EPOLL_CTL_MOD,ch->fd(),&ev) == -1)
        {
            perror("Epoll::updatechannel epoll_ctl() failed.\n");
        }
    }
    else                //未在树上
    {
        if(epoll_ctl(epollfd_,EPOLL_CTL_ADD,ch->fd(),&ev) == -1)
        {
            perror("Epoll::updatechannel epoll_ctl() failed.\n");
        }
        ch -> setinepoll();
    }
}

void Epoll::removechannel(Channel* ch)
{
    if(ch->inpoll())    //已经在树上
    {
        if(epoll_ctl(epollfd_,EPOLL_CTL_DEL,ch->fd(),0) == -1)
        {
            perror("Epoll::removechannel epoll_ctl() failed.\n");
            exit(-1);
        }
    }
}

std::vector<Channel*> Epoll::loop(int timeout)
{
    std::vector<Channel*> channels;

    bzero(events_,sizeof(events_));
    int infds = epoll_wait(epollfd_,events_,MaxEvents,timeout);  //等待timeout时间内，若监视的fd有事件发生，发生的事件会加入到events中
    //返回失败 
    if(infds < 0)//如果infds > 0,表示fd发生事件的数量
    {
        //Reactor模型中，信号比较麻烦，不建议使用
        perror("epoll_wait failed.\n");
        exit(-1);
    }
    //超时
    if(infds == 0)
    {
        //printf("epoll_wait() timeout.\n");
        return channels;
    }
    //如果返回infds > 0,代表事件发生fd的数量
    for(int ii = 0; ii < infds; ii++)   //遍历epoll
    {
        Channel *ch = (Channel*)events_[ii].data.ptr;
        ch -> setrevents(events_[ii].events);   //设置channel的已发生事件
        channels.push_back(ch); //将发生的事件加入到evs容器中
    }
    return channels;
}



