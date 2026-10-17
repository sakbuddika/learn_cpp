#pragma once
#include <iostream>
#include <map>
#include <string>

enum class Severity { INFO, WARNING, ERROR };

class Report
{
    private:
        unsigned int valid_entries = 0;
        unsigned int malformed_lines = 0;
        std::map<Severity, int> severity = {};
        std::map<std::string, int> top_error_messages = {};
    public:
        Report() { std::cout << "DEBUG: Report constructor" << std::endl; }
        ~Report() { std::cout << "DEBUG: Report destructor" << std::endl; }
        void display();

};
