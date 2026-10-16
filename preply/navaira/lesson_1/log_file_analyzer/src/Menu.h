#pragma once
#include <iostream>

class Menu
{
    private:
    public:
        Menu() { std::cout << "DEBUG: Menu constructor" << std::endl; }
        ~Menu() { std::cout << "DEBUG: Menu destructor" << std::endl; }
        void init();
};
