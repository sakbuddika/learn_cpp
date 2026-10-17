#pragma once
#include "Report.h"
#include <iostream>
#include <string>
#include <vector>


class LogReader
{
    private:
        const char DELIMITER = '|';
        const int TOKENS_PER_LINE = 3;
        std::string log_file_name;
        std::vector<std::string> log_lines;
        void read_lines_from_log();
        std::vector<std::string> tokenize(const std::string &);
        bool line_contains_delimiter(const std::string &);
        Report report;
        static std::string trim_message(std::string &);
    public:
        LogReader(
            std::string _log_file_name
        ): log_file_name(_log_file_name)
        { 
            //std::cout << "DEBUG: Report constructor" << std::endl;
        }
        ~LogReader() {
            //std::cout << "DEBUG: Report destructor" << std::endl;
        }
        void analyze();
};
