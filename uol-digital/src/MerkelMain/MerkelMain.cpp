#include "MerkelMain.h"
#include "CSVReader.h"
#include <iostream>
#include <vector>
#include <map>

/** your main function should call this */
void MerkelMain::init()
{
    currentTimeOfTransactions = orderBook.getEarliestTimeOfTransactions();
    int input;
    wallet.addFunds("BTC", 10);
    wallet.addFunds("USDT", 20);
    while(true)
    {
        printMenu();
        input = getUserChoice();
        processUserChoice(input);
    }
}

void MerkelMain::printMenu()
{
    // 1 print Help
    std::cout << "1: Print help " << std::endl;
    // 2 print exchange stats
    std::cout << "2: Print exchange stats " << std::endl;
    // 3 place an ask
    std::cout << "3: Place an ask " << std::endl;
    // 4 place a bid
    std::cout << "4: Place a bid " << std::endl;
    // 5 print wallet
    std::cout << "5: Print wallet " << std::endl;
    // 6 print wallet
    std::cout << "6: Go to next time frame " << std::endl;
    std::cout << "Current Timeframe is : " << currentTimeOfTransactions << std::endl;
    std::cout << "=======================" << std::endl;
    std::cout << "Type in 1-6: ";
}

int MerkelMain::getUserChoice()
{
    int userChoice = 0;
    std::string userChoiceLine;
    std::getline(std::cin, userChoiceLine);
    try
    {
        userChoice = std::stoi(userChoiceLine);
    } 
    catch (const std::exception& e)
    {

    }
    std::cout << "You chose: " << userChoice << std::endl;
    return userChoice;
}

void MerkelMain::printHelp()
{
    std::cout << "Help - choose options from the menu." << std::endl;
    std::cout << "and follow the on screen instructions." << std::endl;
}

void MerkelMain::printExchangeStats()
{
    // std::cout << "INFO: MerkelMain::printExchangeStats OrderBook contains: " << orderBookEntries.size() << " entries " << std::endl;
    for (const std::string& uniqueProduct: orderBook.getUniqueProductsInDataset())
    {
        std::cout << "Product: " << uniqueProduct << std::endl;
        std::map<std::string, OrderBookType> orderTypes{{"bid", OrderBookType::bid}, {"ask", OrderBookType::ask}};
        for (const auto& [key, value] : orderTypes ) 
        {
            std::vector<OrderBookEntry> subsetOfOrders = orderBook.filterOutSubsetOfOrders(orderTypes[key], uniqueProduct, currentTimeOfTransactions);
            std::cout << "Number of " << key << "s seen: " << subsetOfOrders.size() << std::endl;
            std::cout << "Max " << key << ": " << OrderBook::getMaxPrice(subsetOfOrders) << std::endl;
            std::cout << "Min " << key << ": " << OrderBook::getMinPrice(subsetOfOrders) << std::endl;
            std::cout << "24hMax " << key << ": " << orderBook.get24hMaxPrice(orderTypes[key], uniqueProduct, currentTimeOfTransactions) << std::endl;
            std::cout << "24hMin " << key << ": " << orderBook.get24hMinPrice(orderTypes[key], uniqueProduct, currentTimeOfTransactions) << std::endl;
            std::cout << "Spread " << key << ": " << OrderBook::getSpreadPrice(subsetOfOrders) << std::endl;
        }
    }
}

void MerkelMain::enterAsk()
{
    std::string askCSVLine;
    std::cout << "Place an ask. - enter the amount: product, price, amount eg:- BTC/USDT,200,0.5" << std::endl;
    std::getline(std::cin, askCSVLine);
    std::vector<std::string> extractedTokens = CSVReader::tokeniseCSVLines(askCSVLine, ',');
    if (extractedTokens.size() != NUM_TOKENS_PER_ASK_LINE )
    {
        std::cout << "ERROR: MerkelMain::enterAsk Bad input:" << askCSVLine << std::endl;
        return;
    }
    try
    {
        OrderBookEntry orderBookEntry = CSVReader::stringsToOrderBookEntry(
            extractedTokens[1],
            extractedTokens[2],
            currentTimeOfTransactions,
            extractedTokens[0],
            OrderBookType::ask
        );
        orderBookEntry.username = "simuser";

        if(wallet.canFulfillOrder(orderBookEntry))
        {
            std::cout << "Wallet looks good. " << std::endl;
            orderBook.addOrderBookEntryToOrders(orderBookEntry);
        }
        else 
        {
            std::cout << "Wallet has insufficient funds. " << std::endl;
        }
    }
    catch (const std::exception& e)
    {
        std::cout << "ERROR: MerkelMain::enterAsk Bad input: " << askCSVLine << std::endl;
    }
}

void MerkelMain::enterBid()
{
    std::string bidCSVLine;
    std::cout << "Place a bid - enter the amount: product, price, amount eg:- BTC/USDT,200,0.5" << std::endl;
    std::getline(std::cin, bidCSVLine);
    std::vector<std::string> extractedTokens = CSVReader::tokeniseCSVLines(bidCSVLine, ',');
    if (extractedTokens.size() != NUM_TOKENS_PER_BID_LINE )
    {
        std::cout << "ERROR: MerkelMain::enterBid Bad input:" << bidCSVLine << std::endl;
        return;
    }
    try
    {
        OrderBookEntry orderBookEntry = CSVReader::stringsToOrderBookEntry(
            extractedTokens[1],
            extractedTokens[2],
            currentTimeOfTransactions,
            extractedTokens[0],
            OrderBookType::bid
        );
        orderBookEntry.username = "simuser";

        if(wallet.canFulfillOrder(orderBookEntry))
        {
            std::cout << "Wallet looks good. " << std::endl;
            orderBook.addOrderBookEntryToOrders(orderBookEntry);
        }
        else 
        {
            std::cout << "Wallet has insufficient funds. " << std::endl;
        }
    }
    catch (const std::exception& e)
    {
        std::cout << "ERROR: MerkelMain::enterBid Bad input: " << bidCSVLine << std::endl;
    }
}

void MerkelMain::printWallet()
{
    std::cout << "Wallet contains..." << std::endl;
    std::cout << wallet << std::endl;
}

void MerkelMain::gotoNextTimeFrame()
{
    std::cout << "Going to next time frame." << std::endl;
    for (std::string& product : orderBook.getUniqueProductsInDataset())
    {
        std::cout << "matching " << product << std::endl;
        std::vector<OrderBookEntry> sales = orderBook.matchAsksToBids(product, currentTimeOfTransactions);
        std::cout << "Sales: " << sales.size() << std::endl;
        for (OrderBookEntry& sale: sales)
        {
            std::cout << "Sale price: " << sale.price
                << " amount: " << sale.amount << std::endl;
            if(sale.username == "simuser")
            {
                // update the wallet
                wallet.processSale(sale);
            }
        }
    }
    currentTimeOfTransactions = orderBook.getNextTimeOfTransactions(currentTimeOfTransactions);
}

void MerkelMain::processUserChoice(const int userChoice)
{
    switch(userChoice)
    {       
        case 1:
            printHelp();
            break;
        case 2:
            printExchangeStats();
            break;
        case 3:
            enterAsk();
            break;
        case 4:
            enterBid();
            break;
        case 5:
            printWallet();
            break;
        case 6:
            gotoNextTimeFrame();
            break;
    }
}
