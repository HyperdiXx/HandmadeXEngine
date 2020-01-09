#pragma once

#ifndef LOG_H
#define LOG_H

#include <runtime/types.h>
#include <string>
#include <fstream>
#include <iostream>

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

