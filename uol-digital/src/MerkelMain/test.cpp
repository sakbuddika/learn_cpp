#include <iostream>
#include <sstream>
#include <date/date.h>
#include <chrono>
#include <string>

int main(){
    std::string currentTimeString = "2020/03/17 17:01:24.884492";
    std::istringstream currentTimeInputStringStream(currentTimeString);

    date::sys_time<std::chrono::microseconds> timePoint;

    currentTimeInputStringStream >> date::parse("%Y/%m/%d %T", timePoint);

    auto time24hAgo = timePoint - std::chrono::hours(24);

    std::cout << date::format("%Y/%m/%d %T", time24hAgo) << std::endl;

    return 0;
}
