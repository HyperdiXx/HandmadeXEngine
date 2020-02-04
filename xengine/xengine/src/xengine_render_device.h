
#ifndef XENGINE_DEVICE_H
#define XENGINE_DEVICE_H

#include <windows.h>
#include <platform.h>
#include <types.h>

typedef struct persp_camera
{
    real32 near_plane;
    real32 far_plane;

    real32 yaw = -90.0f;
    real32 pitch = 0.0f;

} persp_camera;

typedef struct ortho_camera
{

} ortho_camera;

typedef struct device device;
struct device
{
    HWND window;
    bool32 vsync;
    bool32 fullscreen;
};

internal void look_at(vec3f cam_pos, vec3f cam_target, vec3f up = vec3f(0.0f, 1.0f, 0.0f));

#endif // !XENGINE_DEVICE_H
