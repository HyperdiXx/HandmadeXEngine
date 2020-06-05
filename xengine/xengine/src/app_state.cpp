#include "app_state.h"

#include "xe_ecs.h"
#include "xe_assets.h"
#include "xe_input.h"

namespace application
{
    application_state app_state = {};

    void loadState()
    {
        using namespace xe_ecs;

        xe_assets::model *character = xe_assets::load_model_from_file("assets/nano/nanosuit.obj");
        xe_assets::model *primitive_cube = xe_assets::load_model_from_file("assets/cube.obj");
        xe_assets::model *cerberus = xe_assets::load_model_from_file("assets/cerberus/cerberus.obj");        
        
        xe_assets::anim_model gun = xe_assets::anim_model("assets/m1911/m1911.fbx");
        gun.set_active_animation(0);

        xe_assets::anim_model girl = xe_assets::anim_model("assets/animated/animated_character.fbx");
        girl.set_active_animation(0);

        app_state.addStaticModels("Nano", character);
        app_state.addStaticModels("Cube", primitive_cube);
        app_state.addStaticModels("Cerberus", cerberus);

        app_state.addAnimatedModels("Gun", &gun);
        app_state.addAnimatedModels("Girl", &girl);

        app_state.active_scene = {};

        //@load all ents

        for(int i = 0; i < 20; i++)
            app_state.entities.push_back(entity());
    }

    application_state *getAppState()
    {
        return &app_state;
    }

    void setActiveScene(xe_scene::scene *sc)
    {
        app_state.active_scene = *sc;
    }

    xe_ecs::entity* getEntity()
    {
        xe_ecs::entity *result = nullptr;
        
        std::vector<xe_ecs::entity> &ents = app_state.entities;
        
        for (int i = 0; i < ents.size(); ++i)
        {
            if (!ents[i].active())
            {
                ents[i].setActive(true);
                result = &ents[i];
                break;
            }
        }
        
        return result;
    }

    xe_ecs::entity *getEntityByType(xe_ecs::ENTITY_TYPE type)
    {
        xe_ecs::entity *result = nullptr;

        std::vector<xe_ecs::entity> &ents = app_state.entities;

        for (int i = 0; i < ents.size(); ++i)
        {
            if (!ents[i].getType() == type)
            {
                result = &ents[i];
                break;
            }
        }

        return result;
    }

    void gameUpdate(real32 dt)
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
     
            // Convert to NDC

            glm::vec2 ray_nds = glm::vec2((2.0f * mouse->position.x) / vp_state.width - 1.0f, 1.0f - (2.0f * mouse->position.y) / vp_state.height);

            if (ray_nds.x > -1.0f && ray_nds.x < 1.0f && ray_nds.y > -1.0f && ray_nds.y < 1.0f)
            {
                glm::vec4 homogeneous_coordinates = glm::vec4(ray_nds.x, ray_nds.y, -1.0f, 1.0f);

                auto inverseProj = glm::inverse(camera3D.get_projection_matrix());
                auto inverseView = glm::inverse(glm::mat3(camera3D.get_view_matrix()));

                glm::vec4 ray = inverseProj * homogeneous_coordinates;
                glm::vec3 rayPos = camera3D.pos;
                glm::vec3 rayDir = inverseView * glm::vec3(ray);
                glm::normalize(rayDir);

                ray_cast.origin = rayPos;
                ray_cast.direction = rayDir;

                printf("Ray dir %f %f %f", rayDir.x, rayDir.y, rayDir.z);

                auto& entities = app_state.active_scene.entities;

                for (uint32_t i = 0; i < entities.size(); ++i)
                {
                    xe_ecs::entity *ent = entities[i];
                    
                    xe_ecs::mesh_component *msh_component = ent->find_component<xe_ecs::mesh_component>();

                    if (msh_component)
                    {
                        float t;

                        for (uint32_t j = 0; j < msh_component->model_asset->root->children.size(); ++j)
                        {
                            auto &node_mesh = msh_component->model_asset->root->children[j];

                            for (uint32_t z = 0; z < node_mesh->meshes.size(); ++z)
                            {                                
                                bool isIntersectsAABB = ray_cast.isIntersects(node_mesh->meshes[z]->bounding_box, t);
                                if (isIntersectsAABB)
                                {
                                    printf("Hit mesh %s!!!\n", ent->getName());
                                    break;
                                }
                            }
                        }

                    }                   
                }

                printf("Mouse pos in NDC: \n");
            }

            mouse->is_left_button_pressed = false;
        }
    }

    void application_state::addStaticModels(const char* name, xe_assets::model *model)
    {
        assert(model != nullptr);
        assets_3D.models3D[name] = std::move(*model);
    }

    void application_state::addAnimatedModels(const char* name, xe_assets::anim_model *model)
    {
        assert(model != nullptr);
        assets_3D.animModels3D[name] = std::move(*model);
    }

    xe_assets::model *application_state::getStaticModelByName(const char *name)
    {
        return &assets_3D.models3D[name];
    }

    xe_assets::anim_model *application_state::getAnimatedModelByName(const char *name)
    {
        return &assets_3D.animModels3D[name];
    }
}
