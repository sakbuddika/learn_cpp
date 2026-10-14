#include "OrderBook.h"
#include "CSVReader.h"
#include <map>
#include <algorithm>
#include <chrono>
#include <date/date.h>
#include <iostream>


OrderBook::OrderBook(const std::string csvFileName)
{
    orders = CSVReader::readCSV(csvFileName);
}

std::vector<std::string> OrderBook::getUniqueProductsInDataset()
{
    std::map<std::string,bool> mapOfProducts;
    for (const OrderBookEntry& orderBookEntry: orders)
    {
        // eg:- ETH/BTC -> true
        mapOfProducts[orderBookEntry.product] = true;
    }
    
    std::vector<std::string> uniqueProducts;
    for (const auto& prodctStringBoolPair: mapOfProducts)
    {
        // eg:- ETH/BTC
        uniqueProducts.push_back(prodctStringBoolPair.first);
    }
    return uniqueProducts;
    // std::vector<std::string> uniqueProducts = {};
    // for (const OrderBookEntry& orderBookEntry: orders) {
    //     if ( ! ( std::find( uniqueProducts.begin(), uniqueProducts.end(), orderBookEntry.product) != uniqueProducts.end() ) ) {
    //         uniqueProducts.push_back(orderBookEntry.product);
    //     }
    // }
    // return uniqueProducts;
}

std::vector<OrderBookEntry> OrderBook::filterOutSubsetOfOrders(
    const OrderBookType type,
    const std::string product,
    const std::string timestamp
)
{
    std::vector<OrderBookEntry> orderBookEntries;

    for (const OrderBookEntry& orderBookEntry: orders)
    {
        if  (( orderBookEntry.type == type ) && ( orderBookEntry.product == product ) && ( orderBookEntry.timestamp == timestamp ) )
        {
            orderBookEntries.push_back(orderBookEntry);
        }
    }
    return orderBookEntries;
}

double OrderBook::getMaxPrice(const std::vector<OrderBookEntry>& subsetOfOrders)
{
    double maxPrice{};
    if ( subsetOfOrders.size() > 0 )
    {
        maxPrice = subsetOfOrders[0].price;
        for (const OrderBookEntry& orderBookEntry: subsetOfOrders)
        {
            if ( orderBookEntry.price > maxPrice )
            {
                maxPrice = orderBookEntry.price;
            }
        }
    }
    return maxPrice;
}

double OrderBook::getMinPrice(const std::vector<OrderBookEntry>& subsetOfOrders)
{
    double minPrice{};
    if ( subsetOfOrders.size() > 0 )
    {
        minPrice = subsetOfOrders[0].price;
        for (const OrderBookEntry& orderBookEntry: subsetOfOrders)
        {
            if ( orderBookEntry.price < minPrice )
            {
                minPrice = orderBookEntry.price;
            }
        }
    }
    return minPrice;
}

double OrderBook::getSpreadPrice(
    const std::vector<OrderBookEntry>& subsetOfOrders
)
{
    return OrderBook::getMaxPrice(subsetOfOrders) - OrderBook::getMinPrice(subsetOfOrders);
}

std::string OrderBook::getEarliestTimeOfTransactions()
{
    std::string earliestTime = orders[0].timestamp;
    for (const OrderBookEntry& orderBookEntry : orders)
    {
        if ( earliestTime > orderBookEntry.timestamp )
        {
            earliestTime = orderBookEntry.timestamp;
        }
    }
    return earliestTime;
}

std::string OrderBook::getNextTimeOfTransactions(const std::string& timestamp)
{
    std::string nextTime = getEarliestTimeOfTransactions();
    for(const OrderBookEntry& orderBookEntry: orders)
    {
        if ( timestamp < orderBookEntry.timestamp )
        {
            nextTime = orderBookEntry.timestamp;
            break;
        }
    }
    return nextTime;
}

/** Gets a timestamp in YYYY/mm/dd HH:MM:SS format as a string and returns a 24 hours ago timestamp in the same format*/
std::string OrderBook::get24hAgoTimestamp(const std::string& timestamp)
{
    std::istringstream currentTimeInputStringStream(timestamp);
    date::sys_time<std::chrono::microseconds> timePoint;
    currentTimeInputStringStream >> date::parse("%Y/%m/%d %T", timePoint);
    auto time24hAgo = timePoint - std::chrono::hours(24);
    return date::format("%Y/%m/%d %T", time24hAgo);
}

/** Gets order type, product and timestamp and finds the maximum price for the order type and the product in the last 24 hours */
double OrderBook::get24hMaxPrice(const OrderBookType type, const std::string product, const std::string timestamp)
{
    double maxPrice = OrderBook::getMaxPrice(filterOutSubsetOfOrders(type,product,timestamp));
    std::string timeOfTransactions = OrderBook::get24hAgoTimestamp(timestamp);
    do
    {
        timeOfTransactions = getNextTimeOfTransactions(timeOfTransactions);
        double currentMaxPrice = OrderBook::getMaxPrice(filterOutSubsetOfOrders(type,product,timeOfTransactions));
        if ( maxPrice < currentMaxPrice )
        {
            maxPrice = currentMaxPrice;
        }
    } while (timeOfTransactions < timestamp);
    return maxPrice;
}

/** Gets order type, product and timestamp and finds the minimum price for the order type and the product in the last 24 hours */
double OrderBook::get24hMinPrice(
    const OrderBookType type,
    const std::string product,
    const std::string timestamp
)
{
    double minPrice = OrderBook::getMinPrice(filterOutSubsetOfOrders(type,product,timestamp));
    std::string timeOfTransactions = OrderBook::get24hAgoTimestamp(timestamp);
    do
    {
        timeOfTransactions = getNextTimeOfTransactions(timeOfTransactions);
        double currentMinPrice = OrderBook::getMinPrice(filterOutSubsetOfOrders(type,product,timeOfTransactions));
        if ( minPrice > currentMinPrice )
        {
            minPrice = currentMinPrice;
        }
    } while (timeOfTransactions < timestamp);
    return minPrice;
}
/** Add an order book entry to orders private member, returns nothing*/
void OrderBook::addOrderBookEntryToOrders(const OrderBookEntry& orderBookEntry)
{
    if(orderBookEntry.type != OrderBookType::unknown)
    {
        orders.push_back(orderBookEntry);
        std::sort(orders.begin(),orders.end(),OrderBookEntry::compareByTimestamp);
    }
}

/** Match the asks to bids for a product in a particular timestamp */
std::vector<OrderBookEntry> OrderBook::matchAsksToBids(std::string product, std::string timestamp) 
{
    std::vector<OrderBookEntry> asks = filterOutSubsetOfOrders(OrderBookType::ask, product, timestamp);
    std::vector<OrderBookEntry> bids = filterOutSubsetOfOrders(OrderBookType::bid, product, timestamp);
    std::vector<OrderBookEntry> sales;
    std::sort(asks.begin(), asks.end(), OrderBookEntry::compareByPriceAsc);
    std::sort(bids.begin(), bids.end(), OrderBookEntry::compareByPriceDesc);
    for (OrderBookEntry& ask : asks)
    {
        for (OrderBookEntry& bid : bids)
        {
            if ( bid.price >= ask.price )
            {
                OrderBookEntry sale{timestamp, product, OrderBookType::asksale, ask.price, 0};
                if (bid.username == "simuser")
                {
                    sale.username = "simuser";
                    sale.type = OrderBookType::bidsale;
                }
                if (ask.username == "simuser")
                {
                    sale.username = "simuser";
                    sale.type = OrderBookType::asksale;
                }
                if ( bid.amount == ask.amount )
                {
                    sale.amount = ask.amount;
                    sales.push_back(sale);
                    bid.amount = 0;
                    break;
                }
                if ( bid.amount > ask.amount )
                {
                    sale.amount = ask.amount;
                    sales.push_back(sale);
                    bid.amount = bid.amount - ask.amount;
                    break;
                }
                if ( bid.amount > 0 && bid.amount < ask.amount )
                {
                    sale.amount = bid.amount;
                    sales.push_back(sale);
                    ask.amount = ask.amount - bid.amount;
                    bid.amount = 0;
                    continue;
                }
            }
        }
    }
    return sales;
}
