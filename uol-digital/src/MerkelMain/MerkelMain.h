#pragma once
#include "OrderBookEntry.h"
#include "OrderBook.h"
#include "Wallet.h"
#include <vector>

class MerkelMain
{
    public:
        static const unsigned int NUM_TOKENS_PER_ASK_LINE = 3;
        static const unsigned int NUM_TOKENS_PER_BID_LINE = 3;
        MerkelMain() = default;
        /** Call this to start the sim */
        void init();
    private:
        //std::vector<OrderBookEntry> orderBookEntries;
        OrderBook orderBook{"20200317.csv"};
        //OrderBook orderBook{"temp.csv"};
        std::string currentTimeOfTransactions;
        void loadOrderBook();
        void printMenu();
        void printHelp();
        void printExchangeStats();
        void enterAsk();
        void enterBid();
        void printWallet();
        void gotoNextTimeFrame();
        int getUserChoice();
        void processUserChoice(const int userChoice);
        Wallet wallet;
};
