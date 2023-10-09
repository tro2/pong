#include "Logger.h"

#include <chrono>
#include <ctime>
#include <iostream>

void Logger::log(const std::string& message)
{
	auto time = std::chrono::system_clock::now();
	std::time_t currentTime = std::chrono::system_clock::to_time_t(time);

    std::cout << currentDateTime() << " " << message << std::endl;
}

const std::string Logger::currentDateTime()
{
    time_t now = time(0);
    struct tm tstruct;
    char buf[80];

    localtime_s(&tstruct, &now);
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

    return buf;
}
