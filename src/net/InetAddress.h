#pragma once

#include<arpa/inet.h>
#include<netinet/in.h>
#include<string>

//socket的地址协议类
class InetAddress
{
private:
    sockaddr_in addr_;

public:
    InetAddress();
    InetAddress(const std::string &ip,uint16_t port);
    InetAddress(const sockaddr_in addr);
    ~InetAddress();

    const char* ip() const;
    uint16_t port() const;
    const sockaddr* addr() const;
    void setaddr(sockaddr_in clientaddr);
};