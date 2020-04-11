#pragma once

#include "xe_ecs.h"
#include "xe_core.h"

#include <vector>
#include <map>

namespace xe_graphics
{
    class shadow_map_pass;
    class render_pass;
}

namespace xe_scene
{
    struct scene
    {
        std::string name;
        std::vector<xe_ecs::entity*> entities;
        std::vector<xe_graphics::render_pass*> passes;
        xe_graphics::shadow_map_pass *shadow_pass;
    };

    struct resources
    {
        std::vector<scene*> scenes;         
    };

    struct objects
    {
        std::map<const char*, xe_assets::model> models3D;
    };

    struct entity_manager
    {

    };

    scene create_scene(const char *name);
}
