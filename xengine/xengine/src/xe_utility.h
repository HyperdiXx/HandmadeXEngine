#pragma once

#ifndef XE_UTILITY_H
#define XE_UTILITY_H

#include <string>
#include <fstream>
#include <iostream>

namespace xe_utility
{
    void info(const std::string &info);
    void debug(const std::string& message);
    void error(const std::string& message);
}

#endif // !XE_UTILITY_H


