#include "MerkelMain.h"
#include <iostream>
#include "Wallet.h"

int main()
{
    MerkelMain app{};
    app.init();
    
    // try {
    //     wallet.addFunds("BTC",1.5);
    //     std::cout << "Wallet should contain 1.5 BTC now" << std::endl;
    //     bool result = wallet.containsFunds("BTC",1.5);
    //     std::cout << "Result should be true " << result << std::endl;
    //     wallet.addFunds("ETH",10);
    //     std::cout << "Wallet should contain 10 ETH now" << std::endl;
    //     result = wallet.containsFunds("ETH",10);
    //     std::cout << "Result should be true " << result << std::endl;
    //     std::cout << wallet << std::endl;
    //     result = wallet.removeFunds("BTC",2.0);
    //     std::cout << "Result should be false " << result << std::endl;
    //     result = wallet.removeFunds("BTC",1.0);
    //     std::cout << "Result should be true " << result << std::endl;
    //     result = wallet.removeFunds("BTC",0.5);
    //     std::cout << "Result should be true " << result << std::endl;
    //     wallet.addFunds("ETH",10);
    //     std::cout << "Wallet should contain 20 ETH now" << std::endl;
    //     result = wallet.containsFunds("ETH",20);
    //     std::cout << "Result should be true " << result << std::endl;
    //     std::cout << "Wallet should contain 0 BTC now" << std::endl;
    //     result = wallet.containsFunds("BTC",0);
    //     std::cout << "Result should be true " << result << std::endl;
    //     std::cout << wallet << std::endl;
    // }
    // catch (std::runtime_error e) {
    //     std::cout << "Error " << e.what() << std::endl;
    // }
    // try {
    //     wallet.addFunds("USDT",-10);
    // }
    // catch (std::runtime_error e) {
    //     std::cout << "Error " << e.what() << std::endl;
    // }
    // try {
    //     wallet.removeFunds("USDT",-10);
    // }
    // catch (std::runtime_error e) {
    //     std::cout << "Error " << e.what() << std::endl;
    // }
    // try {
    //     wallet.containsFunds("USDT",-10);
    // }
    // catch (std::runtime_error e) {
    //     std::cout << "Error " << e.what() << std::endl;
    // }
    return 0;
}
