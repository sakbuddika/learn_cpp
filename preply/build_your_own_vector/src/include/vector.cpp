#include "vector.h"
#include <stdexcept>
#include <utility>

IntVector::IntVector()
{
    buffer_ = new int[capacity_];
}

IntVector::IntVector(const IntVector& other)
    :size_(other.size_), capacity_(other.capacity_)
{
    buffer_ = new int[capacity_];
    set_allocations();
    std::memcpy(buffer_, other.buffer_, sizeof(int) * (size_ - 1));
}

IntVector& IntVector::operator=(const IntVector& other)
{
    //std::swap I had issues (no overloaded function matches the argument list size_t, const size_t)
    IntVector v_temp_ = other;
    std::swap(size_, v_temp_.size_);
    std::swap(capacity_, v_temp_.capacity_);
    std::swap(allocations_, v_temp_.allocations_);
    std::swap(buffer_, v_temp_.buffer_);
    return *this;
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

