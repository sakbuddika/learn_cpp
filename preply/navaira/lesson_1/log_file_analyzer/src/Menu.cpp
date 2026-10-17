#include <string>
#include "Menu.h"

void Menu::init()
{
    const std::string DEFAULT_LOG_FILE_NAME = "logs.txt";

    std::string log_file_name = DEFAULT_LOG_FILE_NAME;

    print_header();
    std::cout << "Enter the filename to analyze logs (default: logs.txt): ";

    std::string user_file_name;
    std::getline(std::cin, user_file_name);

    if(user_file_name.length() > 0)
    {
        log_file_name = user_file_name;
    }

    LogReader log_reader(log_file_name);
    log_reader.analyze();
}

void Menu::print_header()
{
    std::cout << "#############################" << std::endl;
    std::cout << "##### Log File Analyzer #####" << std::endl;
    std::cout << "#############################" << std::endl;
}
