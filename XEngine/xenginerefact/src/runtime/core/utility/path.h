#pragma once

#include "string.h"

namespace XEngine
{
    namespace Utility
    {
        class PathSetup
        {
        public:
            PathSetup() {};
            PathSetup(String path);
            PathSetup(std::string path);



        private:
            std::string pathString;
        };
    }
}
