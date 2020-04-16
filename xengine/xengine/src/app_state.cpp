#include "app_state.h"

#include "xe_ecs.h"
#include "xe_assets.h"

namespace application
{
    void load_state(application_state *state)
    {
        using namespace xe_ecs;

        xe_assets::model *character = xe_assets::load_model_from_file("assets/nano/nanosuit.obj");
        xe_assets::model *primitive_cube = xe_assets::load_model_from_file("assets/cube.obj");

        state->assets_3D.models3D.insert(std::pair<const char*, xe_assets::model>("Nano", *character));
        state->assets_3D.models3D.insert(std::pair<const char*, xe_assets::model>("Cube", *primitive_cube));

        state->active_scene = {};

        //@load all ents

        for(int i = 0; i < 20; i++)
            state->entities.push_back(entity());


    }

    xe_ecs::entity* get_entity(application_state *state)
    {
        xe_ecs::entity *result = nullptr;
        
        std::vector<xe_ecs::entity> &ents = state->entities;
        
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

    xe_ecs::entity *get_entity_by_type(application_state *state, xe_ecs::ENTITY_TYPE type)
    {
        xe_ecs::entity *result = nullptr;

        std::vector<xe_ecs::entity> &ents = state->entities;

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
}
