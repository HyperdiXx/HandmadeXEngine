#pragma once 

#ifndef RENDER_COMMANDS_H
#define RENDER_COMMANDS_H


struct RenderClearTarget
{
    real32 x, y, z, a;

    RenderClearTarget() {};
    RenderClearTarget(real32 x_x, real32 y_y, real32 z_z, real32 a_a) : x(x_x), y(y_y), z(z_z), a(a_a) {};
};

struct RenderCommandMesh
{
    GeometryMesh *ptr;
    MaterialInstance *mat_ptr;
};

struct RenderCommandLine
{

};

struct RenderCommandQuad
{

};

enum CommandType
{
    LINE_COMMAND,
    QUAD_COMMAND,
    MESH_COMMAND
};

struct RenderCommand
{
    CommandType type;

    union
    {
        RenderClearTarget clear_command;
        RenderCommandMesh mesh_command;
        RenderCommandQuad quad_command;
        RenderCommandLine line_command;
    };
};

class RenderCommandQueue
{
public:
    typedef void(*RenderCommand)(void*);
    RenderCommandQueue();
    ~RenderCommandQueue();

    void* submit(RenderCommand func_ptr, uint32 size);
    void  executeQueue();

private:
    uint8 *command_buffer_ptr_base;
    uint8 *command_buffer_ptr;
    uint32 command_count = 0;
};

#endif // !RENDER_COMMANDS_H
