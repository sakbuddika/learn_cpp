#pragma once
#include <cstddef>
#include <cstring>

class IntVector {
    public:
        IntVector();
        ~IntVector();
        std::size_t size() const;
        std::size_t capacity() const;
        bool empty() const;
        int& operator[](std::size_t index);
        const int& operator[](std::size_t index) const;
        int& at(std::size_t index); // throws std::out_of_range
        void push_back(int value);
        void pop_back();
        void reserve(std::size_t new_capacity);
        void clear();
        void set_allocations() {allocations_++;}
        int get_allocations() {return allocations_;}
    private:
        const int CAPACITY_MULTIPLIER = 2;
        int* buffer_ = nullptr;
        std::size_t size_ = 0;
        std::size_t capacity_ = 0;
        std::size_t allocations_ = 0;
};
