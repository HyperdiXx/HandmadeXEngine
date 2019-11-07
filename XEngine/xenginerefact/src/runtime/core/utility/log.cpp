#include "log.h"

#include <xenpch.h>
#include "../systems/filesystem.h"



namespace XEngine
{
    void Log::info(const std::string message) 
    {
        std::cout << "Info: " + message << std::endl;
    }

    void Log::debug(const std::string message) 
    {
        std::cout << "Debug: " + message << std::endl;
    }

    void Log::error(const std::string message)
    {
        std::cout << "Error: " + message << std::endl;
    }
}


