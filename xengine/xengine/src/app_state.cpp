#include "app_state.h"

#include "xe_ecs.h"
#include "xe_assets.h"

namespace application
{
    application_state app_state = {};

    void load_state()
    {
        using namespace xe_ecs;

        xe_assets::model *character = xe_assets::load_model_from_file("assets/nano/nanosuit.obj");
        xe_assets::model *primitive_cube = xe_assets::load_model_from_file("assets/cube.obj");

        app_state.assets_3D.models3D.insert(std::pair<const char*, xe_assets::model>("Nano", *character));
        app_state.assets_3D.models3D.insert(std::pair<const char*, xe_assets::model>("Cube", *primitive_cube));

        app_state.active_scene = {};

        //@load all ents

        for(int i = 0; i < 20; i++)
            app_state.entities.push_back(entity());
    }

    application_state * get_app_state()
    {
        return &app_state;
    }

    void set_active_scene(xe_scene::scene *sc)
    {
        app_state.active_scene = *sc;
    }

    xe_ecs::entity* get_entity()
    {
        xe_ecs::entity *result = nullptr;
        
        std::vector<xe_ecs::entity> &ents = app_state.entities;
        
        for (int i = 0; i < ents.size(); ++i)
        {
            if (!ents[i].active())
            {
                ents[i].set_active(true);
                result = &ents[i];
                break;
            }
        }
        
        return result;
    }

    xe_ecs::entity *get_entity_by_type(xe_ecs::ENTITY_TYPE type)
    {
        xe_ecs::entity *result = nullptr;

        std::vector<xe_ecs::entity> &ents = app_state.entities;

        for (int i = 0; i < ents.size(); ++i)
        {
            if (!ents[i].get_type() == type)
            {
                result = &ents[i];
                break;
            }
        }

        return result;
    }

    xe_assets::model *get_model_by_name(const char *name)
    {
        xe_assets::model *result = nullptr;

        xe_scene::objects *obj = &app_state.assets_3D;
       
        result = &obj->models3D[name];

        return result;
    }
}
