#include"Buffer.h"

Buffer::Buffer()
{

}

Buffer::~Buffer()
{

}

void Buffer::append(const char* data,size_t size)
{
    buf_.append(data,size);
}

void Buffer::appendwithhead(const char* data,size_t size)
{
    buf_.append((char*)&size,4);
    buf_.append(data,size);
}


void Buffer::erase(size_t pos,size_t nn)
{
    buf_.erase(pos,nn);
}


size_t Buffer::size()
{
    return buf_.size();
}

const char* Buffer::data()
{
    return buf_.data();
}

void Buffer::clear()
{
    buf_.clear();
}
