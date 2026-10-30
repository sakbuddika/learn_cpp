#include "vector.h"
#include <stdexcept>

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
        capacity_ *= CAPACITY_MULTIPLIER;
        reserve(capacity_);
    }
    buffer_[size_ - 1] = value;
}

void IntVector::pop_back()
{
    buffer_[size_- 1] = 0;
    size_--;
}

void IntVector::reserve(std::size_t new_capacity)
{
    if(new_capacity >= capacity_){
        int* new_buffer_ = new int[new_capacity];
        set_allocations();
        std::memcpy(new_buffer_, buffer_, sizeof(int) * (size_ - 1));
        delete[] buffer_;
        buffer_ = new_buffer_;
        capacity_ = new_capacity;
    }
}

void IntVector::clear()
{
    size_ = 0;
}

bool IntVector::empty() const
{
   return (size_ == 0);
}

int& IntVector::at(std::size_t index)
{
    if (index > (size_ - 1))
        throw std::out_of_range("Index is out of bound");
    return buffer_[index];
}

int& IntVector::operator[](std::size_t index)
{
    return buffer_[index];
}

const int& IntVector::operator[](std::size_t index) const
{
    return buffer_[index];
}

