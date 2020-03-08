#include "xe_platform.h"

bool32 xe_platform::load_library(const char *name)
{
    HMODULE library = LoadLibrary(name);
    if (library)
        return false;
    return true;
}
