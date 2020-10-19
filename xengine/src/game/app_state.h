
#ifndef APP_STATE_H
#define APP_STATE_H

struct WindowOptions
{
    uint32 window_width;
    uint32 window_height;

    bool32 resized;
    bool32 vsync;
    bool32 fullscreen;
};

struct AppOptions
{
    WindowOptions window_options;

    volatile bool32 quit;
    real32 current_time;
    real32 target_frames_per_second;
    bool32 wait_for_events_to_update;
    bool32 pump_events;
};

struct InputState
{
    real32 mouse_position_x;
    real32 mouse_position_y;
    uint64 event_count;
    //OS_Event events[4096];
};

struct AudioPlayer
{
    real32 *sample_out;
    uint32 sample_count_to_output;
    uint32 samples_per_second;
};

typedef struct PlatformState PlatformState;
struct PlatformState
{
    char* executable_folder_absolute_path;
    char* executable_absolute_path;
    char* working_directory_path;

    AppOptions options;
    InputState i_state;

    void* (*LoadOpenGLProcedure)(char *name);
    void* (*AllocateMemory)(void *ptr, uint64 size);
    void* (*ReallocateMemory)(void *ptr, uint64 size);
    void  (*FreeMemory)(void *ptr);

    enum RenderApi
    {
        OPENGL,
        VULKAN,
        DX11
    };

    RenderApi render_api;
};

global PlatformState *platform_state = 0;

#ifdef _MSC_VER
#define GAME_ENTRY_POINT extern "C" __declspec(dllexport)
#else
#define GAME_ENTRY_POINT
#endif

#define APP_LOAD_DATA GAME_ENTRY_POINT void LoadGameCode(PlatformState *ps)
typedef void GameLoadCallback(PlatformState *);
internal void GameLoadStub(PlatformState *_) {}

#define APP_UPDATE GAME_ENTRY_POINT void GameUpdate() 
typedef void GameUpdateCallback(void);
internal void GameUpdateStub(void) {}
#endif
