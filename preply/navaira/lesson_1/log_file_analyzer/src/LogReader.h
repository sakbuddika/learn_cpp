#pragma once
#include <iostream>
#include <string>
#include <vector>


class LogReader
{
    private:
        std::string log_file_name;
        std::vector<std::string> log_lines;
        std::string get_log_file() { return log_file_name; }
        std::vector<std::string> *get_log_lines () { return & log_lines;}
        void read_lines_from_log();
    public:
        LogReader(
            std::string _log_file_name
        ): log_file_name(_log_file_name) { std::cout << "DEBUG: LogReader constructor" << std::endl; }
        ~LogReader() { std::cout << "DEBUG: LogReader destructor" << std::endl; }
        void analyze();
};
