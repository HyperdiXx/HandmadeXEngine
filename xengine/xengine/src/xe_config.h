
// @Define API

#ifndef XE_CONFIG_DATA
#define XE_CONFIG_DATA

#define GAPI_GL
//#define GAPI_DX11
#define WINDOWS_WIDTH 1280
#define WINDOWS_HEIGHT 720
#define ENGINE_NAME "XENGINE"

#include "types.h"

namespace xe_config
{
    struct ConfigData
    {
        const char *name;
        bool32 windowed;
    };

    void parseConfigFile(const char *data, ConfigData *cd);
}

#endif
