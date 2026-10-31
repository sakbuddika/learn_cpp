#include "vector.h"
#include <stdexcept>
#include <utility>

IntVector::IntVector()
{
    buffer_ = new int[capacity_];
}

bool IntVector::operator==(const IntVector& other)
{
    return (this->buffer_ == other.buffer_);
}

bool IntVector::operator!=(const IntVector& other)
{
    return (this->buffer_ != other.buffer_);
}

IntVector::IntVector(const IntVector& other)
    :size_(other.size_), capacity_(other.capacity_)
{
    buffer_ = new int[capacity_];
    set_allocations();
    std::memcpy(buffer_, other.buffer_, sizeof(int) * size_);
}

IntVector& IntVector::operator=(const IntVector& other)
{
    IntVector temp_ = other;
    std::swap(size_,temp_.size_);
    std::swap(capacity_,temp_.capacity_);
    std::swap(allocations_,temp_.allocations_);
    std::swap(buffer_,temp_.buffer_);
    return *this;
}

IntVector::IntVector(IntVector&& other) noexcept
{
    size_ = other.size_;
    capacity_ = other.capacity_;
    allocations_ = other.allocations_;
    buffer_ = other.buffer_;

    other.size_ = 0;
    other.capacity_ = 0;
    other.allocations_ = 0;
    other.buffer_ = nullptr;
}

IntVector& IntVector::operator=(IntVector&& other) noexcept
{
    if (*this != other)
    {
        delete[] buffer_;
        size_ = other.size_;
        capacity_ = other.capacity_;
        allocations_ = other.allocations_;
        buffer_ = other.buffer_;

        other.size_ = 0;
        other.capacity_ = 0;
        other.allocations_ = 0;
        other.buffer_ = nullptr;
    }
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
    if(capacity_ <= size_)
    {
        if(capacity_ == 0)
        {
            capacity_ = 1;
        }
        capacity_ *= CAPACITY_MULTIPLIER;
        reserve(capacity_);
    }
    buffer_[size_] = value;
    size_++;
}

void IntVector::pop_back()
{
    if(size_ > 0)
        size_--;
}

void IntVector::reserve(std::size_t new_capacity)
{
    if(new_capacity >= capacity_){
        int* new_buffer_ = new int[new_capacity];
        set_allocations();
        std::memcpy(new_buffer_, buffer_, sizeof(int) * size_);
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
    if (index >= size_)
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

