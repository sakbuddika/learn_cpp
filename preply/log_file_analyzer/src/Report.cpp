#include "Menu.h"
#include "Report.h"
#include <stdexcept>
#include <algorithm>

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
        std::cout << convert_severity_to_string(severity) << "\t" << num_messages << std::endl;
    }

    std::cout << std::endl;

    std::cout << "Top Error Messages:" << std::endl;
    unsigned int rank = 0;

    // 1. Connection timeout (3)
    for(const auto & map_of_errors : get_top_errors_sort_by_num(error_messages))
        std::cout << ++rank << '.' <<  map_of_errors.cbegin()->first << "\t" << '(' << map_of_errors.cbegin()->second << ')' << std::endl;

    std::cout << std::endl;
}

Severity Report::string_to_severity(const std::string & severity)
{
    if (severity == "INFO")
        return Severity::INFO;
    else if (severity == "WARNING")
        return Severity::WARNING;
    else if (severity == "ERROR")
        return Severity::ERROR;
    else
        throw std::runtime_error(severity + "is not a valid severity type");
}

std::string Report::convert_severity_to_string(const Severity & severity)
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

std::vector<std::map<std::string, int>> Report::get_top_errors_sort_by_num(const std::map<std::string, int> & error_messages)
{
    std::vector<std::map<std::string, int>> sorted_error_messages;
    std::vector<std::map<std::string, int>> top_error_messages;
    for (const auto & pair : error_messages)
    {
        // convert the pair to a map before emplacing back to sorted_error_message
        sorted_error_messages.emplace_back(std::map<std::string, int>{pair});
    }

    std::sort(sorted_error_messages.begin(), sorted_error_messages.end(),
        [](const auto & a, const auto & b)
        {
            // get the iterator by using cbegin (const begin) since we are not modifying
            // then access the second element to get the num errors and compare
            return a.cbegin()->second > b.cbegin()->second;
        }
    );
    // copy MAX_NUM_MESSAGES from sorted_error_messages to top_error_messages
    if(sorted_error_messages.size() >= MAX_NUM_MESSAGES)
        std::copy_n(sorted_error_messages.begin(), MAX_NUM_MESSAGES, std::back_inserter(top_error_messages));
    else
        std::copy(sorted_error_messages.begin(),sorted_error_messages.end(),std::back_inserter(top_error_messages));

    return top_error_messages;
}
