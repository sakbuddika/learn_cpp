#include "Products.h"
#include <iostream>
#include <vector>
#include <fstream>

const unsigned int TOKENS_PER_LINE = 9;

void getLinesFromCSV(const std::string& csvFileName, std::vector<std::string>& csvLines);
std::vector<std::string> tokeniseCSVLines(const std::string& csvLine, const char& delimiter);
void addEntryToProductCatalog(std::vector<Products> &productCatalogs, const std::vector<std::string> &extractedTokens);
void printSummaryOfProductCatalog(const std::vector<Products>& productCatalog);
void printProductDetails(const std::vector<Products> &productCatalog, const int index);

int main()
{
    std::string csvFileName{"product_catalog.csv"};
    std::vector<std::string> csvLines;
    std::vector<Products> productCatalog;

    getLinesFromCSV(csvFileName, csvLines);
    for (const std::string &csvLine : csvLines)
    {
        std::vector<std::string> extractedTokens = tokeniseCSVLines(csvLine, ',');
        if (extractedTokens.size() != TOKENS_PER_LINE)
            continue;
        addEntryToProductCatalog(productCatalog, extractedTokens);
    }
    printSummaryOfProductCatalog(productCatalog);
    return 0;
}

void getLinesFromCSV(const std::string &csvFileName, std::vector<std::string> &csvLines)
{
    std::ifstream csvFile{csvFileName};
    std::string csvLine;
    if (!csvFile.is_open())
        std::cout << "FAIL: File '" << csvFileName << "' was not opened sucessfully." << std::endl;
    while (getline(csvFile, csvLine))
    {
        csvLines.push_back(csvLine);
    }
    csvFile.close();
}

std::vector<std::string> tokeniseCSVLines(const std::string &csvLine, const char &delimiter)
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

void addEntryToProductCatalog(std::vector<Products> & productCatalog, const std::vector<std::string> &extractedTokens)
{
    try
    {
        std::string product_id = extractedTokens[0];
        std::string product_name = extractedTokens[1];
        std::string product_category = extractedTokens[2];
        std::string product_subcategory = extractedTokens[3];
        std::string brand = extractedTokens[4];
        std::string supplier = extractedTokens[5];
        double unit_price = std::stod(extractedTokens[6]);
        double product_cost = std::stod(extractedTokens[7]);
        double product_rating = std::stod(extractedTokens[8]);

        Products product = Products(
            product_id,
            product_name,
            product_category,
            product_subcategory,
            brand,
            supplier,
            unit_price,
            product_cost,
            product_rating);

        productCatalog.push_back(product);
    }
    catch (const std::exception &e)
    {
        std::cout << "FAIL: Failed to parse the line '" << productCatalog.size() + 1 << "'" << std::endl;
    }
}

void printSummaryOfProductCatalog(const std::vector<Products> &productCatalog)
{
    std::cout << "############################################################################" << std::endl;
    std::cout << std::endl << "Read " << productCatalog.size() << " number of valid products " << std::endl;
    printProductDetails(productCatalog, 0);
    printProductDetails(productCatalog, productCatalog.size() - 1);
    std::cout << "############################################################################" << std::endl;
}

void printProductDetails(const std::vector<Products> &productCatalog, const int index)
{
    std::cout << std::endl << "Details of product in index: " << index << std::endl << std::endl;
    try {
        Products product = productCatalog[index];
        std::cout << "\tproduct_id:\t\t" << product.product_id << std::endl;
        std::cout << "\tproduct_name:\t\t" << product.product_name << std::endl;
        std::cout << "\tproduct_category:\t" << product.product_category << std::endl;
        std::cout << "\tproduct_subcategory:\t" << product.product_subcategory << std::endl;
        std::cout << "\tbrand:\t\t\t" << product.brand << std::endl;
        std::cout << "\tsupplier:\t\t" << product.supplier << std::endl;
        std::cout << "\tunit_price:\t\t" << product.unit_price << std::endl;
        std::cout << "\tproduct_cost:\t\t" << product.product_cost << std::endl;
        std::cout << "\tproduct_rating:\t\t" << product.product_rating << std::endl;
    } catch (const std::exception &e) {
        std::cout << "FAIL: Can't find product in index: '" << index << "'" << std::endl;
    }
}  

