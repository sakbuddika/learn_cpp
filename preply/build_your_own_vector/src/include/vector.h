#pragma once
#include <cstddef>
#include <cstring>
#include <stdexcept>
#include <utility>

template <typename T>
class Vector {
    private:
        const T CAPACITY_MULTIPLIER = 2;
        T* buffer_ = nullptr;
        std::size_t size_ = 0;
        std::size_t capacity_ = 0;
        std::size_t allocations_ = 0;
    public:
        Vector()
        {
            buffer_ = new T[capacity_];
        }

        bool operator==(const Vector& other)
        {
            return (this->buffer_ == other.buffer_);
        }

        bool operator!=(const Vector& other)
        {
            return (this->buffer_ != other.buffer_);
        }

        Vector(const Vector& other)
            :size_(other.size_), capacity_(other.capacity_)
        {
            buffer_ = new T[capacity_];
            set_allocations();
            std::memcpy(buffer_, other.buffer_, sizeof(T) * size_);
        }

        Vector& operator=(const Vector& other)
        {
            Vector temp_ = other;
            std::swap(size_,temp_.size_);
            std::swap(capacity_,temp_.capacity_);
            std::swap(allocations_,temp_.allocations_);
            std::swap(buffer_,temp_.buffer_);
            return *this;
        }

        Vector(Vector&& other) noexcept
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

        Vector& operator=(Vector&& other) noexcept
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

        ~Vector()
        {
            delete[] buffer_;
        }

        std::size_t size() const
        {
            return size_;
        }

        std::size_t capacity() const
        {
            return capacity_;
        }

        bool empty() const
        {
            return (size_ == 0);
        }

        T& operator[](std::size_t index)
        {
            return buffer_[index];
        }

        const T& operator[](std::size_t index) const
        {
            return buffer_[index];
        }

        T& at(std::size_t index)
        {
            if (index >= size_)
                throw std::out_of_range("Index is out of bound");
            return buffer_[index];
        }

        void push_back(T value)
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

        void pop_back()
        {
            if(size_ > 0)
                size_--;
        }

        void reserve(std::size_t new_capacity)
        {
            if(new_capacity >= capacity_){
                T* new_buffer_ = new T[new_capacity];
                set_allocations();
                std::memcpy(new_buffer_, buffer_, sizeof(T) * size_);
                delete[] buffer_;
                buffer_ = new_buffer_;
                capacity_ = new_capacity;
            }
        }

        void clear()
        {
            size_ = 0;
        }
        void set_allocations() {allocations_++;}
        T get_allocations() {return allocations_;}
};
