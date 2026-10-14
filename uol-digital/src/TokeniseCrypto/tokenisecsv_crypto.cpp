#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "MerkelMain.h"

const unsigned int TOKENS_PER_LINE = 5;

void getLinesFromCSV(const std::string csvFileName, std::vector<std::string>& csvLines);
std::vector<std::string> tokeniseCSVLines(std::string csvLine, char delimiter);

int main() {
    // std::string csvLine = "2020/03/17 17:01:24.884492,ETH/BTC,bid,0.02187308,7.44564869";
    // std::vector<std::string> extractedTokens = tokeniseCSVLines(csvLine, ',');

    // for (const std::string& token : extractedTokens) {
    //     std::cout << token << std::endl;
    // }

    std::string csvFileName{"20200317.csv"};
    std::vector<std::string> csvLines;
    std::string timestamp;
    std::string product;
    OrderBookType type;
    double price;
    double amount;

    getLinesFromCSV(csvFileName, csvLines);
    std::cout << "Read " << csvLines.size() << " lines " << std::endl;
    for (const std::string &csvLine : csvLines)
    {
        std::vector<std::string> extractedTokens = tokeniseCSVLines(csvLine, ',');
        if (extractedTokens.size() != TOKENS_PER_LINE ) 
            continue;
        try {
            timestamp = extractedTokens[0];
            product = extractedTokens[1];
            type = (extractedTokens[2].compare("bid") == 0) ? OrderBookType::bid : OrderBookType::ask;
            price = std::stod(extractedTokens[3]);
            amount = std::stod(extractedTokens[4]);
        } catch (const std::exception & e) {
            continue;
        }
    }

    return 0;
}

void getLinesFromCSV(const std::string csvFileName, std::vector<std::string>& csvLines)
{
    std::ifstream csvFile{csvFileName};
    std::string csvLine;
    if (csvFile.is_open())
        std::cout << "PASS: File '" << csvFileName << "' opened sucessfully." << std::endl;
    else
        std::cout << "FAIL: File '" << csvFileName << "' was not opened sucessfully." << std::endl;
    while (getline(csvFile, csvLine)) {
        csvLines.push_back(csvLine);
    }
    csvFile.close();
}

std::vector<std::string> tokeniseCSVLines(std::string csvLine, char delimiter) {

    std::vector<std::string> extractedTokens;
    signed int startPosition, endPosition;

    startPosition = csvLine.find_first_not_of(delimiter);
    do {
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