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
    private:
        int* data_ = nullptr;
        std::size_t size_ = 0;
        std::size_t capacity_ = 0;
};
