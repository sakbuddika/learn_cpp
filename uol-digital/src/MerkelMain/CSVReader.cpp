#include "CSVReader.h"
#include <iostream>
#include <fstream>
#include <algorithm>

CSVReader::CSVReader() {

}

std::vector<OrderBookEntry> CSVReader::readCSV(const std::string csvFileName)
{
    std::vector<OrderBookEntry> orderBookEntries;
    
    std::vector<std::string> csvLines = CSVReader::getLinesFromCSV(csvFileName);
    for (const std::string &csvLine : csvLines)
    {
        std::vector<std::string> extractedTokens = CSVReader::tokeniseCSVLines(csvLine, ',');
        try
        {
            OrderBookEntry orderBookEntry = CSVReader::stringsToOrderBookEntry(extractedTokens);
            orderBookEntries.push_back(orderBookEntry);
        } 
        catch (const std::exception &e)
        {
            continue;
        }     
    }
    std::sort(orderBookEntries.begin(), orderBookEntries.end());
    return orderBookEntries;
}

std::vector<std::string> CSVReader::getLinesFromCSV(const std::string csvFileName)
{

    std::vector<std::string> csvLines;
    std::ifstream csvFile{csvFileName};
    std::string csvLine;
    if (csvFile.is_open())
        std::cout << "INFO: CSVReader::getLinesFromCSV File '" << csvFileName << "' opened sucessfully." << std::endl;
    else
        std::cout << "ERROR: CSVReader::getLinesFromCSV File '" << csvFileName << "' was not opened sucessfully." << std::endl;
    while (getline(csvFile, csvLine))
    {
        csvLines.push_back(csvLine);
    }
    csvFile.close();
    std::cout << "INFO: CSVReader::getLinesFromCSV Found '" << csvLines.size() << "' csv lines." << std::endl;
    return csvLines;
}

std::vector<std::string> CSVReader::tokeniseCSVLines(const std::string csvLine, const char delimiter)
{
    std::vector<std::string> extractedTokens;
    signed int startPosition, endPosition;

    startPosition = csvLine.find_first_not_of(delimiter);
    do
    {
        endPosition = csvLine.find_first_of(delimiter, startPosition);
        if (startPosition == csvLine.length() || startPosition == endPosition)
            break;

        std::string extractedToken;
        signed int lengthOfToken;

        if (endPosition >= 0)
            lengthOfToken = endPosition - startPosition;
        else
            lengthOfToken = csvLine.length() - startPosition;

        extractedToken = csvLine.substr(startPosition, lengthOfToken);
        extractedTokens.push_back(extractedToken);
        startPosition = endPosition + 1;

    } while (endPosition != std::string::npos);

    return extractedTokens;

}

OrderBookEntry CSVReader::stringsToOrderBookEntry(
    const std::string _price,
    const std::string _amount,
    const std::string _timestamp,
    const std::string _product,
    OrderBookType _orderBookType
)
{
    double price;
    double amount;

    try {
        price = std::stod(_price);
        amount = std::stod(_amount);
    } catch (const std::exception& e){
        std::cout << "ERROR: CSVReader::stringsToOrderBookEntry bad float!" << _price << std::endl;
        std::cout << "ERROR: CSVReader::stringsToOrderBookEntry bad float!" << _amount << std::endl;
    }

    OrderBookEntry orderBookEntry(
        _timestamp,
        _product,
        _orderBookType,
        price,
        amount
    );

    return orderBookEntry;

}

OrderBookEntry CSVReader::stringsToOrderBookEntry(const std::vector<std::string> extractedTokens)
{
    if ( extractedTokens.size() != CSVReader::NUM_TOKENS_PER_LINE ) {
        std::cout << "ERROR: CSVReader::stringsToOrderBookEntry Found a bad line" << std::endl;
        throw std::exception{};
    }

    std::string timestamp;
    std::string product;
    OrderBookType type;
    double price;
    double amount;

    try
    {
        timestamp = extractedTokens[0];
        product = extractedTokens[1];
        type = OrderBookEntry::stringToOrderBookType(extractedTokens[2]);
        price = std::stod(extractedTokens[3]);
        amount = std::stod(extractedTokens[4]);
    }
    catch (const std::exception& e)
    {
        std::cout << "ERROR: CSVReader::stringsToOrderBookEntry Failed converting tokens" << std::endl;
        throw;
    }

    OrderBookEntry orderBookEntry(
        timestamp,
        product,
        type,
        price,
        amount
    );

    return orderBookEntry;
}
