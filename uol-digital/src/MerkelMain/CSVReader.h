#pragma once
#include "OrderBookEntry.h"
#include <vector>
#include <string>

class CSVReader {
    public:
        static const unsigned int NUM_TOKENS_PER_LINE = 5;
        CSVReader();
        static std::vector<OrderBookEntry> readCSV(const std::string csvFileName);
        static std::vector<std::string> tokeniseCSVLines(const std::string csvLine, const char delimiter);
        static OrderBookEntry stringsToOrderBookEntry(
            const std::string price,
            const std::string amount,
            const std::string timestamp,
            const std::string product,
            OrderBookType orderBookType
        );
    private:
        static std::vector<std::string> getLinesFromCSV(const std::string csvFileName);
        static OrderBookEntry stringsToOrderBookEntry(const std::vector<std::string> extractedTokens);
};
