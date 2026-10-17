#include "Menu.h"
#include "Report.h"
#include <stdexcept>

void Report::display()
{
    system("clear");
    Menu::print_header();
    std::cout << "Log Summary" << std::endl;
    std::cout << "Valid entries: " << valid_entries << std::endl;
    std::cout << "Malformed lines: " << malformed_lines << std::endl;
    std::cout << std::endl;

    // INFO: 4
    for (const auto& [severity, num_messages] : messages_by_severity)
    {
        std::cout << severity_to_string(severity) << "\t" << num_messages << std::endl;
    }

    std::cout << std::endl;

    std::cout << "Top Error Messages:" << std::endl;
    unsigned int rank = 0;

    // 1. Connection timeout (3)
    for (const auto& [error_message, num_messages] : top_error_messages)
        std::cout << ++rank << '.' << error_message << "\t" << '(' << num_messages << ')' << std::endl;


    std::cout << std::endl;
}

Severity Report::string_to_severity(const std::string & severity)
{
    if (severity == " INFO ")
        return Severity::INFO;
    else if (severity == " WARNING ")
        return Severity::WARNING;
    else if (severity == " ERROR ")
        return Severity::ERROR;
    else
        throw std::runtime_error(severity + "is not a valid severity type");
}

std::string Report::severity_to_string(const Severity & severity)
{
    if (severity == Severity::INFO)
        return "INFO";
    else if (severity == Severity::WARNING)
        return "WARNING";
    else if (severity == Severity::ERROR )
        return "ERROR";
    else
        throw std::runtime_error("invalid severity type");
}
