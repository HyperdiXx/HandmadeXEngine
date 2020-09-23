#include "xe_scene.h"

#include "xe_memory.h"

#include "xe_layer.h"

namespace xe_scene
{
    Scene createScene(const char *name)
    {
        Scene created_scene = {};
        
        created_scene.name = name;
        created_scene.entities.reserve(16);
        
        return created_scene;
    }

    void updateSceneLayers(const Scene *scn, real32 dt)
    {
        for (uint32 i = 0; i < scn->layers.size(); ++i)
        {
            xe_graphics::Layer *lay = scn->layers[i];
            lay->update(dt);
        }
    }

    void drawSceneLayers(const Scene *scn)
    {
        for (uint32 i = 0; i < scn->layers.size(); ++i)
        {
            xe_graphics::Layer *lay = scn->layers[i];
            lay->render();
        }
    }

    void pushLayer(Scene *scene, xe_graphics::Layer *layr)
    {
        scene->layers.push_back(layr);
    }

    xe_graphics::Layer *getLayerByName(Scene *scene, xe_graphics::Layer *layr)
    {


        return nullptr;
    }

    void pushPass(Scene *scene, const char *pass_name, xe_graphics::RenderPass *pass)
    {
        scene->passes[pass_name] = pass;
    }

    xe_graphics::RenderPass *getPassByName(Scene *scene, const char *pass_name)
    {
        assert(scene);

        return scene->passes[pass_name];
    }

    /*void pushAnimModel(Scene *scene, xe_assets::AnimModel *animM)
    {
        assert(scene);
        scene->test_anim_models.push_back(animM);
    }*/

    void pushStaticModels(Scene *scene, const char* name, xe_assets::Model *model)
    {
        assert(scene);
        assert(model);
      
        scene->objects->models3D[name] = std::move(*model);
    }

    void pushAnimatedModels(Scene *scene, const char* name, xe_assets::AnimModel *model)
    {
        assert(scene);
        assert(model);

        scene->objects->animModels3D[name] = std::move(*model);
    }

    xe_assets::Model *getStaticModelByName(const Scene *scene, const char *name)
    {
        return &scene->objects->models3D[name];
    }

    xe_assets::AnimModel *getAnimatedModelByName(const Scene *scene, const char *name)
    {
        return &scene->objects->animModels3D[name];
    }

}
