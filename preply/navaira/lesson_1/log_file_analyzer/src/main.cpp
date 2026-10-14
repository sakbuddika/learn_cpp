#include <iostream>
int main()
{
    std::string log_file_name = "logs.txt";
    std::cout << "#############################" << std::endl;
    std::cout << "##### Log File Analyzer #####" << std::endl;
    std::cout << "#############################" << std::endl;
    std::cout << "Enter the filename to analyze logs (default: logs.txt): ";
    std::string user_input;
    std::getline(std::cin, user_input);
    if(user_input.length() > 0)
    {
        log_file_name = user_input;
    }
    std::cout << "Analyzing log file '" << log_file_name << "'...";
    return 0;
}
