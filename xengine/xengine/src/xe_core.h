#pragma once

#ifndef XENGINE_CORE_H
#define XENGINE_CORE_H

#include "types.h"

namespace xe_core
{
    struct file
    {
        uint32 size;
        void *data;
    };

    file read_whole_file(const char *filename);
}

#endif // !XENGINE_CORE_H
