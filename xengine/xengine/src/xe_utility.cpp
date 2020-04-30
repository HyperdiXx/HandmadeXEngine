#include "xe_utility.h"

namespace xe_utility
{
    void info(const std::string& message)
    {
        std::cout << "Info: " + message << "\n";
    }

    void debug(const std::string& message)
    {
        std::cout << "Debug: " + message << "\n";
    }

    void error(const std::string& message)
    {
        std::cout << "Error: " + message << "\n";
    }
}