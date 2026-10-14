#pragma once
#include "OrderBookEntry.h"
#include "CSVReader.h"
#include <map>
#include <string>

class Wallet 
{
    public:
        Wallet() = default;
        /** add funds to the wallet */
        void addFunds(std::string type, double amount);
        /** remove funds from the wallet */
        bool removeFunds(std::string type, double amount);
        /** check whether the wallet has enough funds */
        bool containsFunds(std::string type, double amount);
        /** generate string representation of the wallet */
        std::string toString();
        /** operator << to use with std::cout to print a string representation of the wallet */
        friend std::ostream& operator<<(std::ostream& outputStream, Wallet& wallet);
        /** check whether the order can be fulfilled */
        bool canFulfillOrder(OrderBookEntry orderBookEntry);
        /** update the contents of the wallet assumes the order was made by the owner of the wallet */
        void processSale(OrderBookEntry& sale);

    private:
        std::map<std::string,double> funds;

};

