#include "app_state.h"

#include "xe_ecs.h"
#include "xe_assets.h"
#include "xe_input.h"

namespace application
{
    ApplicationState app_state = {};

    void loadState()
    {
        using namespace xe_ecs;

        xe_assets::Model *character = xe_assets::loadModelFromFile("assets/nano/nanosuit.obj");
        xe_assets::Model *primitive_cube = xe_assets::loadModelFromFile("assets/cube.obj");
        xe_assets::Model *cerberus = xe_assets::loadModelFromFile("assets/cerberus/cerberus.obj");
        
        xe_assets::AnimModel gun = xe_assets::AnimModel("assets/m1911/m1911.fbx");
        gun.set_active_animation(0);

        xe_assets::AnimModel girl = xe_assets::AnimModel("assets/animated/animated_character.fbx");
        girl.set_active_animation(0);

        app_state.addStaticModels("Nano", character);
        app_state.addStaticModels("Cube", primitive_cube);
        app_state.addStaticModels("Cerberus", cerberus);

        app_state.addAnimatedModels("Gun", &gun);
        app_state.addAnimatedModels("Girl", &girl);

        app_state.active_scene = {};

        //@load all ents

        for(int i = 0; i < 20; i++)
            app_state.entities.push_back(Entity());
    }

    ApplicationState *getAppState()
    {
        return &app_state;
    }

    void setActiveScene(xe_scene::Scene *sc)
    {
        app_state.active_scene = *sc;
    }

    xe_ecs::Entity* getEntity()
    {
        xe_ecs::Entity *result = nullptr;
        
        std::vector<xe_ecs::Entity> &ents = app_state.entities;
        
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

    xe_ecs::Entity *getEntityByType(xe_ecs::ENTITY_TYPE type)
    {
        xe_ecs::Entity *result = nullptr;

        std::vector<xe_ecs::Entity> &ents = app_state.entities;

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
        xe_ecs::Camera3DComponent& camera3D = xe_render::getCamera3D();

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

            xe_graphics::GraphicsDevice *device = xe_render::getDevice();
            xe_graphics::Viewport &vp_state = device->getViewport();
     
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
                    xe_ecs::Entity *ent = entities[i];
                    
                    xe_ecs::MeshComponent *msh_component = ent->findComponent<xe_ecs::MeshComponent>();

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

    void ApplicationState::addStaticModels(const char* name, xe_assets::Model *model)
    {
        assert(model != nullptr);
        assets_3D.models3D[name] = std::move(*model);
    }

    void ApplicationState::addAnimatedModels(const char* name, xe_assets::AnimModel *model)
    {
        assert(model != nullptr);
        assets_3D.animModels3D[name] = std::move(*model);
    }

    xe_assets::Model *ApplicationState::getStaticModelByName(const char *name)
    {
        return &assets_3D.models3D[name];
    }

    xe_assets::AnimModel *ApplicationState::getAnimatedModelByName(const char *name)
    {
        return &assets_3D.animModels3D[name];
    }
}
