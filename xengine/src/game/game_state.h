#pragma once

#ifndef GAME_STATE_H
#define GAME_STATE_H

struct Entity;

struct Scene
{
    std::string name;
    DynArray<Entity> entities;
};

struct ClockState
{
    real32 delta_time;
    real32 last_frame = 0.0f;
    real32 start_time = 0;
    uint32 frames_elapsed = 0;
    uint32 fps = 0;
};

struct EditorState
{
    Scene *active_scene;
    
    ClockState timer = {};
    
    bool32 debug_render = false;

    bool32 activate_gizmo = false;
    int gizmo_mode = -1;
};


struct GameState
{
    //LoadedObjects cachedObjects;
    //std::vector<xe_ecs::Entity> entities;


};
#endif