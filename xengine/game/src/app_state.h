#pragma once

#ifndef APP_STATE_H
#define APP_STATE_H

#include "xe_scene.h"

namespace application
{
    struct ClockState
    {
        real32 delta_time;
        real32 last_frame = 0.0f;
        real32 start_time = 0;
        uint32 frames_elapsed = 0;
        uint32 fps = 0;
    };

    struct ApplicationState
    {
        xe_scene::LoadedObjects cachedObjects;
        
        std::vector<xe_ecs::Entity> entities;
        xe_scene::Scene active_scene;

        real32 delta_time;
        real32 last_frame = 0.0f;
        real32 start_time = 0;
        uint32 frames_elapsed = 0;
        uint32 fps = 0;
    };

    ApplicationState *getAppState();

    void setActiveScene(xe_scene::Scene *sc);

    // @Rework init by parsing 
    void loadTestScene(xe_scene::Scene *sc);
    void loadSpheresScene(xe_scene::Scene *sc);

    void loadState();
    xe_ecs::Entity *getEntity();
    xe_ecs::Entity *getEntityByType(xe_ecs::ENTITY_TYPE type);

    void pushEmptyEntity();

    void createPasses(xe_scene::Scene *scene);

    void gameSubmitRenderPasses(real32 dt);
    void gameUpdate(real32 dt);
    void gameInit();
}

#endif // !APP_STATE_H

