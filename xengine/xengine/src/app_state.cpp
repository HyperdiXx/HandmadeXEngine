#include "app_state.h"

#include "xe_ecs.h"
#include "xe_assets.h"
#include "xe_input.h"

namespace application
{
    application_state app_state = {};

    void load_state()
    {
        using namespace xe_ecs;

        xe_assets::model *character = xe_assets::load_model_from_file("assets/nano/nanosuit.obj");
        xe_assets::model *primitive_cube = xe_assets::load_model_from_file("assets/cube.obj");
        xe_assets::model *cerberus = xe_assets::load_model_from_file("assets/cerberus/cerberus.obj");
        //xe_assets::anim_model *gun = xe_assets::load_anim_model_from_file("assets/m1911/m1911.fbx");

        app_state.animated_test_gun = xe_assets::AnimatedModel("assets/m1911/m1911.fbx");
        app_state.animated_test_gun.set_active_animation(0);

        app_state.girl = xe_assets::AnimatedModel("assets/animated/animated_character.fbx");
        app_state.girl.set_active_animation(0);

        app_state.assets_3D.models3D.insert(std::pair<const char*, xe_assets::model>("Nano", *character));
        app_state.assets_3D.models3D.insert(std::pair<const char*, xe_assets::model>("Cube", *primitive_cube));
        app_state.assets_3D.models3D.insert(std::pair<const char*, xe_assets::model>("Cerberus", *cerberus));

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

    void game_update(real32 dt)
    {
        xe_ecs::camera3d_component& camera3D = xe_render::get_camera3D();

        if (xe_input::pressed(xe_input::KEYBOARD_S))
        {
            camera3D.pos -= camera3D.speed * dt * camera3D.target;
        }

        if (xe_input::pressed(xe_input::KEYBOARD_W))
        {
            camera3D.pos += camera3D.speed * dt * camera3D.target;
        }

        if (xe_input::pressed(xe_input::KEYBOARD_A))
        {
            camera3D.pos -= camera3D.speed * dt * camera3D.right;
        }

        if (xe_input::pressed(xe_input::KEYBOARD_D))
        {
            camera3D.pos += camera3D.speed * dt * camera3D.right;
        }

        if (xe_input::pressed(xe_input::KEYBOARD_V))
        {
            //transform_component *tr = light_ent.find_component<transform_component>();
            //tr->position.x += 0.8f * sin(dt);
            //tr->position.z += 0.8f * cos(dt);
        }

        if (xe_input::pressed(xe_input::KEYBOARD_B))
        {
            //transform_component *tr = light_ent.find_component<transform_component>();
            //tr->position.x -= 0.8f * sin(dt);
            //tr->position.z -= 0.8f * cos(dt);
        }

        xe_input::mouse_state *mouse = xe_input::get_mouse_state();

        if (mouse->is_right_button_pressed)
        {
            real32 xoffset = mouse->position.x - mouse->dt_position.x;
            real32 yoffset = mouse->dt_position.y - mouse->position.y;

            //printf("DX: %f\n", xoffset);
            //printf("DY: %f\n", yoffset);

            camera3D.mouse_move(xoffset, yoffset);
        }

        if (mouse->is_left_button_pressed)
        {
            ray ray_cast = {};

            xe_graphics::graphics_device *device = xe_render::get_device();
            xe_graphics::viewport &vp_state = device->get_viewport();
     
            glm::vec2 viewport_pos_mouse = glm::vec2((mouse->position.x / vp_state.width) * 2.0f - 1.0f, ((mouse->position.y / vp_state.height) * 2.0f - 1.0f));
            if (viewport_pos_mouse.x > -1.0f && viewport_pos_mouse.x < 1.0f && viewport_pos_mouse.y > -1.0f && viewport_pos_mouse.y < 1.0f)
            {
                printf("Mouse pos in NDC: \n");
            }

            mouse->is_left_button_pressed = false;
        }
    }
}
