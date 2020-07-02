#pragma once

#include "xe_ecs.h"
#include "xe_core.h"

#include <vector>
#include <map>

namespace xe_graphics
{
    class ShadowMapPass;
    class RenderPass;
    class Layer;
}

namespace application
{
    struct ApplicationState;
}

namespace xe_scene
{   
    struct Objects
    {
        std::unordered_map<const char*, xe_assets::Model> models3D;
        std::unordered_map<const char*, xe_assets::AnimModel> animModels3D;
    };

    struct Scene
    {
        std::string name;
        std::vector<xe_ecs::Entity*> entities;
        std::vector<xe_graphics::RenderPass*> passes;
        std::vector<xe_graphics::Layer*> layers;
        xe_graphics::ShadowMapPass *shadow_pass;
        xe_ecs::Entity *directional_light;
    };

    struct Resources
    {
        std::vector<Scene*> scenes;
    };

    Scene createScene(const char *name);
   
    void updateSceneLayers(const Scene *scn);
    void drawSceneLayers(const Scene *scn);

    // @Rework init by parsing 
    void loadTestScene(Scene *sc);
    void loadSpheresScene(Scene *sc);
}
