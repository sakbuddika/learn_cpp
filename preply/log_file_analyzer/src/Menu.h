#pragma once
#include "LogReader.h"
#include <iostream>

class Menu
{
    private:
        std::string log_file_name;
    public:
        Menu() {
            //std::cout << "DEBUG: " << __FILE__ << " constructor" << std::endl;
        }
        ~Menu() {
            //std::cout << "DEBUG: " << __FILE__ << " destructor" << std::endl;
        }
        static void init();
        static void print_header();
};
