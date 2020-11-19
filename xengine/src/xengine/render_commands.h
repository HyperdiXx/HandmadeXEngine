#pragma once 

#ifndef RENDER_COMMANDS_H
#define RENDER_COMMANDS_H


enum CommandType
{
    CLEAR_COMMAND,
    VIEWPORT_COMMAND,
    STATIC_MODEL_MODEL,
    ANIM_MODEL_COMMAND,
    LINE_COMMAND,
    QUAD_COMMAND
};

struct RenderCommandClearTarget
{
    CommandType type;
    real32 x, y, z, a;
};

class RenderCommandStaticModel
{
public:
    RenderCommandStaticModel() { };
    RenderCommandStaticModel(Transform *transf, Model *mod, Material *mat);
   
    ~RenderCommandStaticModel();

    void execute();

private:    
    Transform *transform_data;
    Model *static_model_ptr;
    Material *mat_ptr;
};

class PostProcPassCommand
{
public:

    PostProcPassCommand() {};
    PostProcPassCommand(Material *mat, RenderPass *pass);

    ~PostProcPassCommand();

    void execute();

private:
    RenderPass *pass_ptr;
    Material *mat_ptr;
};

struct RenderCommandAnimatedModel
{
    CommandType type;
    
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
