#pragma once

#include <types.h>
#include <string>
#include <fstream>
#include <iostream>

namespace xe_utility
{
    void info(const std::string &info);
    void debug(const std::string& message);
    void error(const std::string& message);
}
