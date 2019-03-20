#include "src/application/xenpch.h"
#include "filesystem.h"
#include <shlobj.h>



std::wstring FileSystemGetLogFolder()
{
    wchar_t buffer[MAX_PATH];
    std::wstring result;

    HRESULT hr = SHGetFolderPath(0,
        CSIDL_LOCAL_APPDATA,
        0,
        SHGFP_TYPE_CURRENT,
        (LPSTR)buffer);

    result = buffer;

    return (result);

}
