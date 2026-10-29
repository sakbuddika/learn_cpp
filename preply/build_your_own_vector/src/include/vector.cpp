#include "vector.h"
#include <cstddef>
#include <cstring>

IntVector::IntVector()
{
    buffer_ = new int[capacity_];
}

IntVector::~IntVector()
{
    delete[] buffer_;
}

std::size_t IntVector::size() const
{
    return size_;
}

std::size_t IntVector::capacity() const
{
    return capacity_;
}

void IntVector::push_back(int value)
{
    size_++;
    if(capacity_ < size_)
    {
        if(capacity_ == 0)
        {
            capacity_ = 1;
        }
        capacity_ *= 2;
    }
    int* new_buffer_ = new int[capacity_];
    std::memcpy(new_buffer_, buffer_, sizeof(int));
    delete[] buffer_;
    buffer_ = new_buffer_;
}

void reserve(std::size_t new_capacity)
{

}


