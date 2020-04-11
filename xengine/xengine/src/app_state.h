#pragma once

#include "xe_scene.h"

namespace application
{
    struct application_state
    {
        xe_scene::objects assets_3D;
        std::vector<xe_ecs::entity> entities;
        xe_scene::scene active_scene;
    };

    void load_state(application_state *state);
    xe_ecs::entity* get_entity(application_state *state);
}
