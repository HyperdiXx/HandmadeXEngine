#include "xe_scene.h"

namespace xe_scene
{
    scene create_scene(const char *name)
    {
        scene created_scene = {};
        
        created_scene.name = name;
        created_scene.entities.reserve(16);

        return created_scene;
    }
}
