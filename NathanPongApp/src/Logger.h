#pragma once

#include <string>


class Logger
{
public:
    static void log(const std::string& message);

private:
    static const std::string currentDateTime();
};


