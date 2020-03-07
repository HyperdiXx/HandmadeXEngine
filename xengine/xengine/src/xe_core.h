#pragma once

#ifndef XENGINE_CORE_H
#define XENGINE_CORE_H

#include "types.h"
#include <string>

namespace xe_core
{
    struct file
    {
        uint32 size;
        void *data;
    };

    file read_whole_file(const char *filename);
    std::string read_file_string(const char *file_path);
}

#endif // !XENGINE_CORE_H
