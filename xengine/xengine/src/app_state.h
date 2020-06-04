#pragma once

#include "xe_scene.h"

namespace application
{   
    struct application_state
    {
        xe_scene::objects assets_3D;
        std::vector<xe_ecs::entity> entities;
        xe_scene::scene active_scene;

        real32 delta_time;
        real32 last_frame = 0.0f;
        real32 start_time = 0;
        uint32 frames_elapsed = 0;
        uint32 fps = 0;

        xe_assets::AnimatedModel animated_test_gun;
        xe_assets::AnimatedModel girl;
    };
   
    application_state *get_app_state();
    
    void set_active_scene(xe_scene::scene *sc);
    
    void load_state();
    xe_ecs::entity *get_entity();
    xe_ecs::entity *get_entity_by_type(xe_ecs::ENTITY_TYPE type);
    xe_assets::model *get_model_by_name(const char* name);

    void game_update(real32);
}
