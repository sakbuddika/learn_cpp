    #include "Wallet.h"
    #include <string>
    #include <iostream>

    void Wallet::addFunds(std::string type, double amount)
    {
        if ( amount < 0 )
            throw( std::runtime_error("Cannot add " + std::to_string(amount) + " to " + type));
        if ( funds.count(type) == 0 )
            funds[type] = amount;
        else
            funds[type] += amount;
    }

    bool Wallet::containsFunds(std::string type, double amount)
    {
        std::cout << "type is : " << type << std::endl;
        std::cout << "amount is : " << std::to_string(amount) << std::endl;
        if ( amount < 0 )
            throw( std::runtime_error("Cannot check " + type + " contains " + std::to_string(amount)));

        if (( funds.count(type) > 0 ) && ( funds[type] >= amount ))
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    bool Wallet::removeFunds(std::string type, double amount)
    {
        if ( amount < 0 )
            throw( std::runtime_error("Cannot remove " + std::to_string(amount) + " from " + type));

        if (containsFunds(type,amount))
        {
            funds[type] -= amount;
            return true;
        }
        else
        {
            return false;
        }
    }

    std::string Wallet::toString()
    {
        std::string walletString;
        for (std::pair<std::string,double> pair : funds)
        {
            walletString += pair.first + " : " + std::to_string(pair.second) + "\n";
        }
        return walletString;
    }

    std::ostream& operator<<(std::ostream& outputStream, Wallet& wallet)
    {
        outputStream << wallet.toString();
        return outputStream;
    }

    bool Wallet::canFulfillOrder(OrderBookEntry orderBookEntry)
    {
        std::vector<std::string> extractedTokens = CSVReader::tokeniseCSVLines(orderBookEntry.product, '/');

        if ( orderBookEntry.type == OrderBookType::ask )
        {
            std::cout << "It is an OrderBookType::ask" << std::endl;
            double amount = orderBookEntry.amount;
            std::string currency = extractedTokens[0];
            return containsFunds(currency, amount);
        } 
        else if ( orderBookEntry.type == OrderBookType::bid )
        {
            std::cout << "It is an OrderBookType::bid" << std::endl;
            double amount = orderBookEntry.amount * orderBookEntry.price;
            std::string currency = extractedTokens[1];
            return containsFunds(currency, amount);
        }
        std::cout << "It is an OrderBookType::unknown" << std::endl;
        return false;
    }

    void Wallet::processSale(OrderBookEntry& sale)
    {
        std::vector<std::string> extractedTokens = CSVReader::tokeniseCSVLines(sale.product, '/');

        if ( sale.type == OrderBookType::asksale )
        {
            double outgoingAmount = sale.amount;
            std::string outgoingCurrency = extractedTokens[0];
            double incomingAmount = sale.amount * sale.price;
            std::string incomingCurrency = extractedTokens[1];

            funds[incomingCurrency] += incomingAmount;
            funds[outgoingCurrency] -= outgoingAmount;
        } 
        else if ( sale.type == OrderBookType::bidsale )
        {
            double incomingAmount = sale.amount;
            std::string incomingCurrency = extractedTokens[0];
            double outgoingAmount = sale.amount * sale.price;
            std::string outgoingCurrency = extractedTokens[1];

            funds[incomingCurrency] += incomingAmount;
            funds[outgoingCurrency] -= outgoingAmount;
        }
    }
