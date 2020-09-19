
typedef struct win32_game_code win32_game_code;
struct win32_game_code
{
    HMODULE dll;
    GameLoadCallback* LoadGameCode;
    GameUpdateCallback* GameUpdate;
};

internal bool LoadGameCode(win32_game_code *data, const char *name)
{
    data->dll = LoadLibraryA(name);

    if (!data->dll)
    {
        return false;
    }

    data->LoadGameCode = (GameLoadCallback*)GetProcAddress(data->dll, "LoadGameCode");
    data->GameUpdate = (GameUpdateCallback*)GetProcAddress(data->dll, "GameUpdate");

    if (!data->LoadGameCode || !data->GameUpdate)
    {
        return false;
    }

    return true;
}

internal void GameUpdateWin32(win32_game_code *app_code)
{
    //FILETIME last_write_time = W32_GetLastWriteTime(global_app_dll_path);
    //if (CompareFileTime(&last_write_time, &app_code->last_dll_write_time))
   // {
        //app_code->HotUnload();
        //W32_AppCodeUnload(app_code);
        //W32_AppCodeLoad(app_code);
        //app_code->HotLoad(&global_os);
    //}
}

