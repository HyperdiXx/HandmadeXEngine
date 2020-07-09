#pragma once

#include "xe_ecs.h"
#include "xe_core.h"

#include "xenpch.h"

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
    struct LoadedObjects
    {
        std::unordered_map<const char*, xe_assets::Model> models3D;
        std::unordered_map<const char*, xe_assets::AnimModel> animModels3D;
    };

    struct Scene
    {
        std::string name;
        std::vector<xe_ecs::Entity*> entities;
        
        LoadedObjects *objects;

        std::unordered_map<const char*, xe_graphics::RenderPass*> passes;
        std::vector<xe_graphics::Layer*> layers;
        xe_graphics::ShadowMapPass *shadow_pass;
        xe_ecs::Entity *directional_light;
    };

    struct Resources
    {
        std::vector<Scene*> scenes;
    };

    Scene createScene(const char *name);
   
    void updateSceneLayers(const Scene *scn, real32 dt);
    void drawSceneLayers(const Scene *scn);

    void pushLayer(Scene *scene, xe_graphics::Layer *layr);   
    xe_graphics::Layer *getLayerByName(Scene *scene, xe_graphics::Layer *layr);

    void pushPass(Scene *scene, const char *pass_name, xe_graphics::RenderPass *pass);
    xe_graphics::RenderPass *getPassByName(Scene *scene, const char *pass_name);

    void pushStaticModels(Scene *scene, const char* name, xe_assets::Model *model);
    void pushAnimatedModels(Scene *scene, const char* name, xe_assets::AnimModel *model);

    xe_assets::Model* getStaticModelByName(const Scene *scene, const char *name);
    xe_assets::AnimModel* getAnimatedModelByName(const Scene *scene, const char *name);

}
