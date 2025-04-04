#include"Acceptor.h"

Acceptor::Acceptor(EventLoop* loop,const std::string &ip,uint16_t port):loop_(loop)
{
    servsock_ = new Socket(createnonblocking());
    InetAddress servaddr(ip,port);
    servsock_->setreuseaddr(true); 
    servsock_->settcpnodelay(true);
    servsock_->setreuseport(true);
    servsock_->setkeepalive(true);
   
    servsock_->bind(servaddr);
    servsock_->listen();

    acceptchannel_ = new Channel(loop_,servsock_->fd());
    acceptchannel_->setreadcallback(std::bind(&Acceptor::newconnection,this));
    acceptchannel_->enablereading();
}

Acceptor::~Acceptor()
{
    delete servsock_;
    delete acceptchannel_;
}


#include"Connection.h"
void Acceptor::newconnection()
{
    InetAddress clientaddr;
    Socket *clientsock = new Socket(servsock_->accept(clientaddr));
    printf("accept client(fd=%d,ip=%s,port=%d) ok.\n",clientsock->fd(),clientaddr.ip(),clientaddr.port());

    Connection* conn = new Connection(loop_,clientsock);
}