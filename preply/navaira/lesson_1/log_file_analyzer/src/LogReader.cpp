#include "LogReader.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

void LogReader::analyze()
{
    std::cout << "Analyzing log file '" << get_log_file() << "'..." << std::endl << std::endl;
    read_lines_from_log();
    std::vector<std::string> *log_lines = get_log_lines();
    std::cout << log_lines->size() << std::endl;
}

void LogReader::read_lines_from_log()
{
    std::ifstream log_file(get_log_file());
    if(!log_file.is_open())
    {
        std::cout << "ERROR: failed to open file '" << get_log_file() << "'" << \
            ", File: " << __FILE__ << ", Function: " << __PRETTY_FUNCTION__ << ", Line:" << __LINE__ << std::endl;
    }
    std::vector<std::string> *log_lines = get_log_lines();
    std::string log_line;
    while(getline(log_file, log_line))
    {
        log_lines->push_back(log_line);
    }
}

