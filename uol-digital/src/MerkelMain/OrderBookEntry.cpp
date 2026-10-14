#include "OrderBookEntry.h"
#include <vector>

OrderBookEntry::OrderBookEntry(
    std::string _timestamp,
    std::string _product,
    OrderBookType _type,
    double _price,
    double _amount,
    std::string _username
) : timestamp(_timestamp), product(_product), type(_type), amount(_amount), price(_price), username(_username)
{
}
OrderBookType OrderBookEntry::stringToOrderBookType(
    const std::string action
)
{
    if (action == "ask")
    {
        return OrderBookType::ask;
    }
    else if (action == "bid")
    {
        return OrderBookType::bid;
    }
    else 
    {
        return OrderBookType::unknown;
    }
}
