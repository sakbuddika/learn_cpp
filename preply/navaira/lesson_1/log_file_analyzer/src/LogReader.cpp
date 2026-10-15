#include "LogReader.h"
#include <iostream>
#include <fstream>

bool LogReader::can_open_file(std::string log_file_name)
{
    std::ifstream istrm(log_file_name, std::ios::binary);
    if(!istrm.is_open())
    {
        std::cout << "ERROR: failed to open file '" << log_file_name << "'" << std::endl;
        return false;
    }
    return true;
}
