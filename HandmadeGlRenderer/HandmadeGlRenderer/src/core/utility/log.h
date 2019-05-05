#pragma once

#ifndef LOG_H
#define LOG_H

#include "../types.h"
#include <string>
#include <fstream>
#include <iostream>

#define LOG(i) std::cout << i;
#define LOGSTRING(a, b) std::cout << a << b << "\n";

namespace XEngine
{
    class Log
    {
    public:
        static void info(const std::string message);
        static void debug(const std::string message);
        static void error(const std::string message);
    };

}
#endif // !LOG_H

