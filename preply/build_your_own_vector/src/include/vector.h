#pragma once
#include <cstddef>
#include <cstring>
#include <stdexcept>
#include <utility>
#include <new>

template <typename T>
class Vector {
    private:
        const int CAPACITY_MULTIPLIER = 2;
        T* buffer_ = nullptr;
        std::size_t size_ = 0;
        std::size_t capacity_ = 0;
        std::size_t allocations_ = 0;
        T* buffer() {return static_cast<T*>(buffer_);}
        const T* buffer() const {return static_cast<const T*>(buffer_);}
        void _ensure_capacity()
        {
            if(capacity_ <= size_)
            {
                size_t new_capacity = (capacity_ == 0)  ? 1 : capacity_ *= CAPACITY_MULTIPLIER;
                reserve(new_capacity);
            }
        }
    public:
        Vector()
        {
            buffer_ = static_cast<T*>(::operator new(capacity_ * sizeof(T)));
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
            :size_(other.size_),capacity_(other.capacity_)
        {
            buffer_ = static_cast<T*>(::operator new(capacity_ * sizeof(T)));
            T* other_buffer_ = static_cast<T*>(other.buffer_);

            set_allocations();
            for (size_t i = 0; i < size_; ++i)
            {
                // placement new: re-construct element at the new address
                new(buffer_ + i)  T(*(other_buffer_ + i));
            }
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
                ::operator delete(buffer_);
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
            for (size_t i = 0; i < size_; ++i)
            {
                buffer_[i].~T();
            }
            ::operator delete(buffer_);
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
            return buffer()[index];
        }

        const T& operator[](std::size_t index) const
        {
            return buffer()[index];
        }

        T& at(std::size_t index)
        {
            if (index >= size_)
                throw std::out_of_range("Index is out of bound");
            return buffer()[index];
        }

        void push_back(const T& value) // copies value
        {
            _ensure_capacity();
            new (buffer() + size_)  T(value);
            size_++;
        }

        void push_back(T&& value) // move value
        {
            _ensure_capacity();
            new (buffer() + size_)  T(value);
            size_++;
        }

        void pop_back()
        {
            if(size_ > 0)
            {
                buffer_[size_ - 1].~T();
                size_--;
            }
        }

        void reserve(std::size_t new_capacity)
        {
            if(new_capacity >= capacity_){
                T* new_buffer_ = static_cast<T*>(::operator new(new_capacity * sizeof(T)));

                set_allocations();
                for (size_t i = 0; i < size_; ++i)
                {
                    new(new_buffer_ + i)  T(*(buffer_ + i));
                    buffer_[i].~T();
                }
                ::operator delete(buffer_);
                buffer_ = new_buffer_;
                capacity_ = new_capacity;
            }
        }

        void clear()
        {
            for (size_t i = 0; i < size_; ++i)
            {
                buffer_[i].~T();
            }
            size_ = 0;
        }
        void set_allocations() {allocations_++;}
        int get_allocations() {return allocations_;}
};
