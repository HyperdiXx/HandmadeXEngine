
#ifndef XENGINE_RENDERING_H
#define XENGINE_RENDERING_H

#ifdef _MSC_VER
#pragma once
#endif  

#include <windows.h>
#include <platform.h>
#include <types.h>

struct persp_camera
{
    real32 near_plane;
    real32 far_plane;

    real32 yaw = -90.0f;
    real32 pitch = 0.0f;
};

struct ortho_camera
{

};

struct render_command
{

};

struct vertex_buffer
{

};

struct index_buffer
{

};

struct vertex_array
{

};

typedef struct device_context device_context;
struct device_context
{

};

typedef struct device device;
struct device
{
    HWND window;
    bool32 vsync;
    bool32 fullscreen;
};

struct shader
{
    uint32 id;
    char *vertex_code;
    char *fragment_code;
};

struct framebuffer
{
    uint32 id;
};

struct texture2D
{
    uint32 id;
};


#endif // !XENGINE_RENDERING_H
