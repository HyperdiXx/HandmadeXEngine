#include "log.h"

#include <xenpch.h>
#include <runtime/core/systems/filefunc.h>

namespace XEngine
{
    void Log::info(const std::string& message) 
    {
        std::cout << "Info: " + message << "\n";
    }

    void Log::debug(const std::string& message) 
    {
        std::cout << "Debug: " + message << "\n";
    }

    void Log::error(const std::string& message)
    {
        std::cout << "Error: " + message << "\n";
    }
}


