#include "app_state.h"

#include "xe_ecs.h"
#include "xe_assets.h"
#include "xe_input.h"
#include "xe_layer.h"
#include "xe_render_pass.h"
#include "xe_utility.h"

namespace application
{
    ApplicationState app_state = {};

    void loadState()
    {
        using namespace xe_ecs;        
        
        app_state.active_scene = {};

        app_state.active_scene.objects = &app_state.cachedObjects;

        xe_assets::Model *character = xe_assets::loadModelFromFile("assets/nano/nanosuit.obj");
        xe_assets::Model *primitive_cube = xe_assets::loadModelFromFile("assets/cube.obj");
        //xe_assets::Model *cerberus = xe_assets::loadModelFromFile("assets/cerberus/cerberus.fbx");

        xe_assets::AnimModel gun = xe_assets::AnimModel("assets/m1911/m1911.fbx");
        gun.set_active_animation(0);

        xe_assets::AnimModel girl = xe_assets::AnimModel("assets/animated/girl_idle.fbx");
        girl.set_active_animation(0);

        xe_scene::pushStaticModels(&app_state.active_scene, "Nano", character);
        xe_scene::pushStaticModels(&app_state.active_scene, "Cube", primitive_cube);
        //xe_scene::pushStaticModels(&app_state.active_scene, "Cerberus", cerberus);

        xe_scene::pushAnimatedModels(&app_state.active_scene, "Gun", &gun);
        xe_scene::pushAnimatedModels(&app_state.active_scene, "Girl", &girl);

        //@load all ents

        for (int i = 0; i < 20; i++)
        {
            pushEmptyEntity();
        }
    }

    std::vector<xe_ecs::Entity*>& getEntities()
    {
       return app_state.active_scene.entities;
    }

    ApplicationState *getAppState()
    {
        return &app_state;
    }

    void setActiveScene(xe_scene::Scene *sc)
    {
        //Setting pointer to cache
        sc->objects = &app_state.cachedObjects;
        app_state.active_scene = *sc;
    }

    void loadTestScene(xe_scene::Scene * sc)
    {
        application::ApplicationState *app_state = application::getAppState();
        xe_scene::Scene &activeS = app_state->active_scene;

        xe_ecs::Entity* test_entity = application::getEntity();
        test_entity->setEntityType(xe_ecs::ENTITY_TYPE::ENT_STATIC_OBJECT);
        test_entity->setEntityName("Nano character");

        xe_ecs::Entity* light_entity = application::getEntity();
        light_entity->setEntityType(xe_ecs::ENTITY_TYPE::ENT_DIR_LIGHT);

        xe_ecs::Entity* plane_entity = application::getEntity();
        plane_entity->setEntityType(xe_ecs::ENTITY_TYPE::ENT_WATER);
        plane_entity->setEntityName("Plane water");

        assert(test_entity != nullptr);
        assert(light_entity != nullptr);
        assert(plane_entity != nullptr);

        xe_ecs::MeshComponent *character_mesh = new xe_ecs::MeshComponent();
        character_mesh->model_asset = xe_scene::getStaticModelByName(&activeS, "Nano");

        xe_ecs::TransformComponent *nano_transform = new xe_ecs::TransformComponent();
        nano_transform->setTranslation(-20.0f, -9.0f, -50.0f);

        test_entity->addComponent(character_mesh);
        test_entity->addComponent(nano_transform);

        for (int i = 0; i < 10; ++i)
        {
            xe_ecs::Entity* ent = application::getEntity();
            ent->setEntityType(xe_ecs::ENTITY_TYPE::ENT_STATIC_OBJECT);
            ent->setEntityName(std::string("Cube") + std::to_string(i));

            xe_ecs::TransformComponent *transform = new xe_ecs::TransformComponent();
            transform->setTranslation(30.0f * (i - 5), 0.0f, -5.0f * (i + 1));
            transform->setScale(0.2f, 0.2f, 0.2f);

            xe_ecs::MeshComponent *loading_model = new xe_ecs::MeshComponent();
            loading_model->model_asset = xe_scene::getStaticModelByName(&activeS, "Cube");
            loading_model->draw_with_color = true;

            ent->addComponent(transform);
            ent->addComponent(loading_model);

            sc->entities.push_back(ent);
        }

        xe_ecs::MeshComponent *cube_mesh = new xe_ecs::MeshComponent();
        cube_mesh->model_asset = xe_scene::getStaticModelByName(&activeS, "Cube");
        cube_mesh->draw_with_color = true;

        xe_ecs::DirLight *dl = new xe_ecs::DirLight();
        dl->color = glm::vec3(0.8f, 0.7f, 0.8f);
        dl->intensity = 0.9f;

        xe_ecs::TransformComponent *light_transform = new xe_ecs::TransformComponent();
        light_transform->setTranslation(5.0f, 10.0f, -5.0f);
        light_transform->setScale(0.2f, 0.2f, 0.2f);

        light_entity->addComponent(dl);
        light_entity->addComponent(light_transform);
        light_entity->addComponent(cube_mesh);

        xe_ecs::MeshComponent *plane_mesh = new xe_ecs::MeshComponent();
        plane_mesh->model_asset = xe_scene::getStaticModelByName(&activeS, "Cube");

        xe_ecs::TransformComponent *transform_plane = new xe_ecs::TransformComponent();

        transform_plane->setTranslation(3.0f, -10.0f, 75.0f);
        transform_plane->setScale(10.0f, 0.001f, 10.0f);

        xe_ecs::WaterComponent *water_component = new xe_ecs::WaterComponent();

        water_component->water_tex = xe_render::getTexture2DResource("water");

        plane_entity->addComponent(plane_mesh);
        plane_entity->addComponent(transform_plane);
        plane_entity->addComponent(water_component);

        xe_ecs::Entity* ent_line = application::getEntity();
        ent_line->setEntityType(xe_ecs::ENTITY_TYPE::ENT_LINE);

        xe_ecs::LineMeshComponent *line_mesh = new xe_ecs::LineMeshComponent();
        line_mesh->line_co = new xe_graphics::Line();

        glm::vec3 start_point = glm::vec3(0.0f, 1.0f, -15.0f);
        glm::vec3 end_point = glm::vec3(5.0f, 1.0f, -15.0f);

        bool32 is_create_line = xe_render::createLineMesh(start_point, end_point, line_mesh->line_co);

        ent_line->addComponent(line_mesh);

        sc->entities.push_back(test_entity);
        sc->entities.push_back(light_entity);
        sc->entities.push_back(plane_entity);
        sc->entities.push_back(ent_line);

        sc->directional_light = light_entity;
    }

    void loadSpheresScene(xe_scene::Scene * sc)
    {
        //@ PBR scene

        xe_ecs::Entity *sphere_entity = application::getEntity();
        sphere_entity->setEntityType(xe_ecs::ENTITY_TYPE::ENT_PRIMITIVE_OBJECT);

        xe_ecs::PBRMaterialComponent *sphere_material = new xe_ecs::PBRMaterialComponent();

        xe_ecs::SphereComponent *sphere_compon = new xe_ecs::SphereComponent();
        sphere_compon->diffuse = xe_render::getTexture2DResource("albedo_iron");

        xe_ecs::TransformComponent *trans_component = new xe_ecs::TransformComponent();
        trans_component->setTranslation(0.0f, -4.0f, -5.0f);
        trans_component->setScale(4.0f, 4.0f, 4.0f);

        sphere_entity->addComponent(sphere_compon);
        sphere_entity->addComponent(trans_component);

        sc->entities.push_back(sphere_entity);
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

    void pushEmptyEntity()
    {
        app_state.entities.push_back(xe_ecs::Entity());
    }

    void createPasses(xe_scene::Scene *scene)
    {
        using namespace xe_scene;
        using namespace xe_graphics;

        assert(scene);

        RenderPass *render_pass_2D = new RenderPass2D();
        render_pass_2D->init();

        xe_render::setRenderPass(render_pass_2D);

        RenderPass *main_render_pass = new RenderPass3D();
        main_render_pass->init();
        main_render_pass->setScene(&app_state.active_scene);

        RenderPass *gamma_correction = new GammaCorrectionPass();
        gamma_correction->init();

        ShadowMapPass shadow_pass = {};
        //shadow_pass.init();
        //shadow_pass.setScene(&current_app_state->active_scene);

        //PbrPass pbr_setup = {};
        //pbr_setup.init();

        //pbr_scene.passes.push_back(&pbr_setup);

        pushPass(scene, "layer3D", main_render_pass);
        pushPass(scene, "layer2D", render_pass_2D);
        pushPass(scene, "gammaCorrectionLayer", gamma_correction);
    }

    void gameSubmitRenderPasses(real32 dt)
    {
        using namespace xe_graphics;
        
        xe_render::beginFrame();

        RenderPass *main_pass = xe_scene::getPassByName(&app_state.active_scene, "layer3D");
        RenderPass *render_pass_2D = xe_scene::getPassByName(&app_state.active_scene, "layer2D");
        RenderPass *gamma_correction = xe_scene::getPassByName(&app_state.active_scene, "gammaCorrectionLayer");
       
        render_pass_2D->update(dt);
        xe_scene::updateSceneLayers(&app_state.active_scene, dt);

        RenderPass3D *pass3D = dynamic_cast<RenderPass3D*>(main_pass);
        
        pass3D->update(dt);
        pass3D->render();

        Texture2D* pass_texture = main_pass->getColorTexture();

        gamma_correction->setColorTexture(pass_texture);
        gamma_correction->render();

        //pbr_setup.update(current_app_state->delta_time);
        //pbr_setup.render();

        
        render_pass_2D->render();

       
        xe_scene::drawSceneLayers(&app_state.active_scene);

        //guiLayer.update(current_app_state->delta_time);
        //guiLayer.render();

        xe_render::endFrame();
    }

    void gameUpdate(real32 dt)
    {
        xe_input::update();

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

        xe_input::MouseState *mouse = xe_input::getMouseState();

        if (mouse->isRightButtonPressed)
        {
            real32 xoffset = mouse->position.x - mouse->dtPosition.x;
            real32 yoffset = mouse->dtPosition.y - mouse->position.y;

            //printf("DX: %f\n", xoffset);
            //printf("DY: %f\n", yoffset);

            camera3D.mouse_move(xoffset, yoffset);
        }

        if (mouse->isLeftButtonPressed)
        {
            mouse->isLeftButtonPressed = false;
            
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

                //ray_cast.origin = rayPos;
                //ray_cast.direction = rayDir;

                printf("Ray dir %f %f %f\n", rayDir.x, rayDir.y, rayDir.z);

                bool32 is_ent_hitted = false;

                auto& entities = getEntities();

                for (uint32 i = 0; i < entities.size(); ++i)
                {
                    if (is_ent_hitted)
                    {
                        break;
                    }

                    xe_ecs::Entity *ent = entities[i];

                    xe_ecs::MeshComponent *msh_component = ent->findComponent<xe_ecs::MeshComponent>();
                    xe_ecs::TransformComponent *transform = ent->findComponent<xe_ecs::TransformComponent>();

                    if (msh_component && transform)
                    {
                        real32 t = FLT_MAX;
                        real32 lastT = std::numeric_limits<float>::max();
                       
                        glm::mat4 transformMatrix = xe_render::IDENTITY_MATRIX;

                        transformMatrix = glm::translate(transformMatrix, transform->position);
                        transformMatrix = glm::scale(transformMatrix, transform->scale);

                        for (uint32 j = 0; j < msh_component->model_asset->root->children.size(); ++j)
                        {
                            auto &node_mesh = msh_component->model_asset->root->children[j];

                            ray_cast.origin = glm::inverse(transformMatrix) * glm::vec4(rayPos, 1.0f);
                            ray_cast.direction = glm::inverse(glm::mat3(transformMatrix)) * rayDir;

                            for (uint32 z = 0; z < node_mesh->meshes.size(); ++z)
                            {
                                bool isIntersectsAABB = ray_cast.isIntersects(node_mesh->meshes[z]->bounding_box, t);
                                if (isIntersectsAABB)
                                {                                    
                                    xe_utility::info(ent->getName() + "\n");
                                    is_ent_hitted = true;
                                    break;
                                }
                            }
                        }

                    }
                }

                printf("Mouse pos in NDC: \n");
            }
        }
    }

    void gameInit()
    {

#ifndef GAPI_GL        
#define GAPI_GL

        using namespace xe_graphics;

        application::loadState();

        xe_scene::Scene new_scene = xe_scene::createScene("TestScene");
        xe_scene::Scene pbr_scene = xe_scene::createScene("PBRScene");

        application::loadTestScene(&new_scene);
        application::loadSpheresScene(&pbr_scene);
        
        Layer *two_dimensional = new Layer2D();

        Layer *three_dimensional = new Layer3D();

        GUILayer guiLayer = {};

        xe_scene::pushLayer(&new_scene, three_dimensional);
        xe_scene::pushLayer(&new_scene, two_dimensional);
        
        createPasses(&new_scene);

        application::setActiveScene(&new_scene);
#endif 

#ifdef GAPI_DX11


#endif

    //------------------------------------------------------------//
        GraphicsDevice *device = xe_render::getDevice();
        device->clearColor(0.1f, 0.1f, 0.1f, 1.0f);

    }
}
