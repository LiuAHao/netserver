#include"InetAddress.h"

//socket的地址协议类实现

InetAddress::InetAddress()
{
}

InetAddress::InetAddress(const std::string &ip,uint16_t port)
{
    addr_.sin_family = AF_INET;
    addr_.sin_addr.s_addr = inet_addr(ip.c_str());
    addr_.sin_port = htons(port);
}

InetAddress::InetAddress(const sockaddr_in addr):addr_(addr)
{
}

InetAddress::~InetAddress()
{
}

const char* InetAddress::ip() const
{
    return inet_ntoa(addr_.sin_addr);
}

uint16_t InetAddress::port() const
{
    return ntohs(addr_.sin_port);
}

const sockaddr* InetAddress::addr() const
{
    return (sockaddr*)&addr_;
}

void InetAddress::setaddr(sockaddr_in clientaddr)
{
    addr_ = clientaddr;
}