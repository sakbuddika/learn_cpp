#pragma once
#include <iostream>
#include <map>
#include <string>

enum class Severity { INFO, WARNING, ERROR };


class Report
{
    private:
        unsigned int valid_entries = 0;
        unsigned int malformed_lines = 0;
        std::map<Severity, int> messages_by_severity = {};
        std::map<std::string, int> top_error_messages = {};
        std::string severity_to_string(const Severity &);
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
        void increment_top_error_messages(const std::string &message) {top_error_messages[message]++;}
};
