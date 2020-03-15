#pragma once

#include "xe_ecs.h"

#include "xe_core.h"
#include <vector>

#include <unordered_map>

namespace xe_scene
{
    struct scene
    {
        int number;
        std::string name;
        std::vector<xe_ecs::entity*> entities;
        std::vector<xe_graphics::render_pass*> passes;
    };

    struct resources
    {
        std::vector<scene*> scenes;         
    };

    struct entity_manager
    {

    };


    void init();
}
