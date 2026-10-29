#include "vector.h"

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
    std::memcpy(new_buffer_, buffer_, sizeof(int) * (size_ - 1));
    delete[] buffer_;
    buffer_ = new_buffer_;
    buffer_[size_ - 1] = value;
}

void IntVector::reserve(std::size_t new_capacity)
{
    int* new_buffer_ = new int[new_capacity];
    std::memcpy(new_buffer_, buffer_, sizeof(int));
    delete[] buffer_;
    buffer_ = new_buffer_;
}

int& IntVector::operator[](std::size_t index)
{
    return buffer_[index];
}

