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

        void addStaticModels(const char* name, xe_assets::model *model);
        void addAnimatedModels(const char* name, xe_assets::anim_model *model);

        xe_assets::model* getStaticModelByName(const char *name);
        xe_assets::anim_model* getAnimatedModelByName(const char *name);
    };
   
    application_state *getAppState();
    
    void setActiveScene(xe_scene::scene *sc);
    
    void loadState();
    xe_ecs::entity *getEntity();
    xe_ecs::entity *getEntityByType(xe_ecs::ENTITY_TYPE type);

    void gameUpdate(real32);
}
