#pragma once
#include <string>

enum class OrderBookType { bid, ask, unknown, asksale, bidsale };

class OrderBookEntry
{
public:
    std::string timestamp;
    std::string product;
    OrderBookType type;
    double price;
    double amount;
    std::string username;
    OrderBookEntry(
        std::string timestamp,
        std::string product,
        OrderBookType type,
        double price,
        double amount,
        std::string username = "dataset"
    );
    bool operator < ( const OrderBookEntry& orderBookEntry  ) const { return (timestamp < orderBookEntry.timestamp); }
    static OrderBookType stringToOrderBookType(const std::string action);
    static bool compareByTimestamp(const OrderBookEntry& orderBookEntry1, const OrderBookEntry& orderBookEntry2)
    {
        return orderBookEntry1.timestamp < orderBookEntry2.timestamp;
    }
    static bool compareByPriceAsc(const OrderBookEntry& orderBookEntry1, const OrderBookEntry& orderBookEntry2)
    {
        return orderBookEntry1.price < orderBookEntry2.price;
    }
    static bool compareByPriceDesc(const OrderBookEntry& orderBookEntry1, const OrderBookEntry& orderBookEntry2)
    {
        return orderBookEntry1.price > orderBookEntry2.price;
    }
};

