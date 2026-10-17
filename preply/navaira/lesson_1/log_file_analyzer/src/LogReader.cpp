#include "LogReader.h"
#include <fstream>
#include <algorithm>
#include <stdexcept>
#include <typeinfo>

void LogReader::analyze()
{
    std::cout << "Analyzing log file '" << log_file_name << "'..." << std::endl << std::endl;
    read_lines_from_log();
    for (const std::string& line : log_lines)
    {
        const std::vector<std::string> extracted_tokens = tokenize(line);
        if(extracted_tokens.size() != TOKENS_PER_LINE)
        {
            report.increment_malformed_lines();
            continue;
        }
        else
        {
            std::string severity = extracted_tokens[1];
            std::string error_message = extracted_tokens[2];
            try
            {
                report.increment_messages_by_severity(report.string_to_severity(severity));
                report.increment_valid_entries();
                report.increment_top_error_messages(error_message);
            }
            catch (std::exception &e)
            {
                report.increment_malformed_lines();
                continue;
            }
        }
    }
    report.display();
}

void LogReader::read_lines_from_log()
{
    std::ifstream log_file(log_file_name);
    if(!log_file.is_open())
    {
        std::cout << "ERROR: failed to open file '" << log_file_name << "'" << std::endl;
        return;
    }
    std::string log_line;
    while(getline(log_file, log_line))
    {
        log_lines.push_back(log_line);
    }
}

std::vector<std::string> LogReader::tokenize(const std::string & log_line)
{   
    std::vector<std::string> extracted_tokens;
    signed int start_position, end_position;

    start_position = log_line.find_first_not_of(DELIMITER);
    do{
        end_position = log_line.find_first_of(DELIMITER, start_position);
        // found nothing
        if(start_position == log_line.length() || start_position == end_position)
            break;
        std::string extracted_token;
        signed int length_of_token;
        // found something
        if(end_position >= 0)
            length_of_token = end_position - start_position;
        else
            length_of_token = log_line.length() - start_position;
        
        extracted_token = log_line.substr(start_position, length_of_token);
        extracted_tokens.push_back(extracted_token);
        // look for the next one
        start_position = end_position + 1;
    } while (end_position != std::string::npos);

    return extracted_tokens;
}

