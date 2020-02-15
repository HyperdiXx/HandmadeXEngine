#pragma once

#ifndef LOG_H
#define LOG_H

#include <types.h>
#include <string>
#include <fstream>
#include <iostream>

namespace xe_utility
{   
    void info(const std::string& message);
    void debug(const std::string& message);
    void error(const std::string& message);
}
#endif // !LOG_H

