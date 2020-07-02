#include "xe_scene.h"

#include "xe_memory.h"

#include "app_state.h"

#include "xe_render_pass.h"

namespace xe_scene
{
    Scene createScene(const char *name)
    {
        Scene created_scene = {};
        
        created_scene.name = name;
        created_scene.entities.reserve(16);
        
        return created_scene;
    }

    void updateSceneLayers(const Scene *scn)
    {
        application::ApplicationState *app_state = application::getAppState();
     
        for (uint32 i = 0; i < scn->layers.size(); ++i)
        {
            xe_graphics::Layer *lay = scn->layers[i];
            lay->update(app_state->delta_time);
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

    void loadTestScene(Scene *sc)
    {
        application::ApplicationState *app_state = application::getAppState();
     
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
        character_mesh->model_asset = app_state->getStaticModelByName("Nano");

        xe_ecs::TransformComponent *nano_transform = new xe_ecs::TransformComponent();
        nano_transform->setTranslation(-20.0f, -9.0f, -50.0f);

        test_entity->addComponent(character_mesh);
        test_entity->addComponent(nano_transform);

        for (int i = 0; i < 10; ++i)
        {
            xe_ecs::Entity* ent = application::getEntity();
            ent->setEntityType(xe_ecs::ENTITY_TYPE::ENT_STATIC_OBJECT);
            ent->setEntityName(std::string("Cube number " + i));

            xe_ecs::TransformComponent *transform = new xe_ecs::TransformComponent();
            transform->setTranslation(30.0f * (i - 5), 0.0f, -5.0f * (i + 1));
            transform->setScale(0.2f, 0.2f, 0.2f);

            xe_ecs::MeshComponent *loading_model = new xe_ecs::MeshComponent();
            loading_model->model_asset = app_state->getStaticModelByName("Cube");
            loading_model->draw_with_color = true;

            ent->addComponent(transform);
            ent->addComponent(loading_model);

            sc->entities.push_back(ent);
        }

        xe_ecs::MeshComponent *cube_mesh = new xe_ecs::MeshComponent();
        cube_mesh->model_asset = app_state->getStaticModelByName("Cube");
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
        plane_mesh->model_asset = app_state->getStaticModelByName("Cube");

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
        line_mesh->line_co = alloc_mem xe_graphics::Line();

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

    void loadSpheresScene(Scene *sc)
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
}
