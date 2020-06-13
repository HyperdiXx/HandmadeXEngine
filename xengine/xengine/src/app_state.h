#pragma once

#include "xe_scene.h"

namespace application
{   
    struct ApplicationState
    {
        xe_scene::Objects assets_3D;
        std::vector<xe_ecs::Entity> entities;
        xe_scene::Scene active_scene;

        real32 delta_time;
        real32 last_frame = 0.0f;
        real32 start_time = 0;
        uint32 frames_elapsed = 0;
        uint32 fps = 0;

        void addStaticModels(const char* name, xe_assets::Model *model);
        void addAnimatedModels(const char* name, xe_assets::AnimModel* model);

        xe_assets::Model* getStaticModelByName(const char *name);
        xe_assets::AnimModel* getAnimatedModelByName(const char *name);
    };
   
    ApplicationState *getAppState();
    
    void setActiveScene(xe_scene::Scene *sc);
    
    void loadState();
    xe_ecs::Entity *getEntity();
    xe_ecs::Entity *getEntityByType(xe_ecs::ENTITY_TYPE type);

    void gameUpdate(real32);
}
