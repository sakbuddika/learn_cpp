#pragma once
#include "OrderBookEntry.h"
#include "CSVReader.h"
#include <string>
#include <vector>

class OrderBook {
    public:
        OrderBook(const std::string csvFileName);
        std::vector<std::string> getUniqueProductsInDataset();
        std::vector<OrderBookEntry> filterOutSubsetOfOrders(const OrderBookType type, const std::string product, const std::string timestamp);
        std::string getEarliestTimeOfTransactions();
        std::string getNextTimeOfTransactions(const std::string& timestamp);
        static std::string get24hAgoTimestamp(const std::string& timestamp);
        double get24hMaxPrice(const OrderBookType type, const std::string product, const std::string timestamp);
        double get24hMinPrice(const OrderBookType type, const std::string product, const std::string timestamp);
        static double getMaxPrice(const std::vector<OrderBookEntry>& subsetOfOrders);
        static double getMinPrice(const std::vector<OrderBookEntry>& subsetOfOrders);
        static double getSpreadPrice(const std::vector<OrderBookEntry>& subsetOfOrders);
        void addOrderBookEntryToOrders(const OrderBookEntry& orderBookEntry);
        std::vector<OrderBookEntry> matchAsksToBids(std::string product, std::string timestamp);
    private:
        std::vector<OrderBookEntry> orders;
};
