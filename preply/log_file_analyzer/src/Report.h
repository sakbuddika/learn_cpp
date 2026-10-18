#pragma once
#include <iostream>
#include <map>
#include <string>
#include <vector>

enum class Severity { INFO, WARNING, ERROR };


class Report
{
    private:
        const unsigned int MAX_NUM_MESSAGES = 3;
        unsigned int valid_entries = 0;
        unsigned int malformed_lines = 0;
        std::map<Severity, int> messages_by_severity = {};
        std::map<std::string, int> error_messages = {};
        std::string convert_severity_to_string(const Severity &);
        std::vector<std::map<std::string, int>> get_top_errors_sort_by_num(const std::map<std::string, int> &);
    public:
        Report() {
            //std::cout << "DEBUG: " << __FILE__ << " constructor" << std::endl;
        }
        ~Report() {
            //std::cout << "DEBUG: " << __FILE__ << " destructor" << std::endl;
        }
        void display();
        void increment_malformed_lines() { malformed_lines++; }
        void increment_valid_entries() { valid_entries++; }
        Severity string_to_severity(const std::string &);
        void increment_messages_by_severity(const Severity &severity) { messages_by_severity[severity]++;}
        void increment_error_messages(const std::string &message) {error_messages[message]++;}
};
