#include "xe_scene.h"

#include "xe_memory.h"

#include "app_state.h"

#include "xe_render_pass.h"

namespace xe_scene
{
    scene create_scene(const char *name)
    {
        scene created_scene = {};
        
        created_scene.name = name;
        created_scene.entities.reserve(16);
        
        return created_scene;
    }

    void draw_scene_layers(scene *scn)
    {
        for (uint32 i = 0; i < scn->layers.size(); ++i)
        {
            xe_graphics::layer *lay = scn->layers[i];
            lay->render();
        }
    }

    void load_test_scene(scene *sc)
    {
        application::application_state *app_state = application::getAppState();
     
        xe_ecs::entity* test_entity = application::getEntity();
        test_entity->set_entity_type(xe_ecs::ENTITY_TYPE::ENT_STATIC_OBJECT);

        xe_ecs::entity* light_entity = application::getEntity();
        light_entity->set_entity_type(xe_ecs::ENTITY_TYPE::ENT_DIR_LIGHT);

        xe_ecs::entity* plane_entity = application::getEntity();
        plane_entity->set_entity_type(xe_ecs::ENTITY_TYPE::ENT_WATER);

        assert(test_entity != nullptr);
        assert(light_entity != nullptr);
        assert(plane_entity != nullptr);

        xe_ecs::mesh_component *character_mesh = new xe_ecs::mesh_component();
        character_mesh->model_asset = app_state->getStaticModelByName("Nano");

        xe_ecs::transform_component *nano_transform = new xe_ecs::transform_component();
        nano_transform->set_translation(-20.0f, -9.0f, -50.0f);

        test_entity->add_component(character_mesh);
        test_entity->add_component(nano_transform);

        for (int i = 0; i < 10; ++i)
        {
            xe_ecs::entity* ent = application::getEntity();
            ent->set_entity_type(xe_ecs::ENTITY_TYPE::ENT_STATIC_OBJECT);

            xe_ecs::transform_component *transform = new xe_ecs::transform_component();
            transform->set_translation(30.0f * (i - 5), 0.0f, -5.0f * (i + 1));
            transform->set_scale(0.2f, 0.2f, 0.2f);

            xe_ecs::mesh_component *loading_model = new xe_ecs::mesh_component();
            loading_model->model_asset = app_state->getStaticModelByName("Cube");
            loading_model->draw_with_color = true;

            ent->add_component(transform);
            ent->add_component(loading_model);

            sc->entities.push_back(ent);
        }

        xe_ecs::mesh_component *cube_mesh = new xe_ecs::mesh_component();
        cube_mesh->model_asset = app_state->getStaticModelByName("Cube");
        cube_mesh->draw_with_color = true;

        xe_ecs::dir_light *dl = new xe_ecs::dir_light();
        dl->color = glm::vec3(0.8f, 0.7f, 0.8f);
        dl->intensity = 0.9f;

        xe_ecs::transform_component *light_transform = new xe_ecs::transform_component();
        light_transform->set_translation(5.0f, 10.0f, -5.0f);
        light_transform->set_scale(0.2f, 0.2f, 0.2f);

        light_entity->add_component(dl);
        light_entity->add_component(light_transform);
        light_entity->add_component(cube_mesh);

        xe_ecs::mesh_component *plane_mesh = new xe_ecs::mesh_component();
        plane_mesh->model_asset = app_state->getStaticModelByName("Cube");

        xe_ecs::transform_component *transform_plane = new xe_ecs::transform_component();

        transform_plane->set_translation(3.0f, -10.0f, 75.0f);
        transform_plane->set_scale(10.0f, 0.001f, 10.0f);

        xe_ecs::water_component *water_component = new xe_ecs::water_component();

        water_component->water_tex = xe_render::get_texture2D_resource("water");

        plane_entity->add_component(plane_mesh);
        plane_entity->add_component(transform_plane);
        plane_entity->add_component(water_component);

        xe_ecs::entity* ent_line = application::getEntity();
        ent_line->set_entity_type(xe_ecs::ENTITY_TYPE::ENT_LINE);

        xe_ecs::line_mesh_component *line_mesh = new xe_ecs::line_mesh_component();
        line_mesh->line_co = alloc_mem xe_graphics::line();

        glm::vec3 start_point = glm::vec3(0.0f, 1.0f, -15.0f);
        glm::vec3 end_point = glm::vec3(5.0f, 1.0f, -15.0f);

        bool32 is_create_line = xe_render::create_line_mesh(start_point, end_point, line_mesh->line_co);

        ent_line->add_component(line_mesh);
      
        sc->entities.push_back(test_entity);
        sc->entities.push_back(light_entity);
        sc->entities.push_back(plane_entity);
        sc->entities.push_back(ent_line);

        sc->directional_light = light_entity;
    }

    void load_spheres_scene(scene *sc)
    {
        //@ PBR scene

        xe_ecs::entity *sphere_entity = application::getEntity();
        sphere_entity->set_entity_type(xe_ecs::ENTITY_TYPE::ENT_PRIMITIVE_OBJECT);

        xe_ecs::pbr_material_component *sphere_material = new xe_ecs::pbr_material_component();

        xe_ecs::sphere_component *sphere_compon = new xe_ecs::sphere_component();
        sphere_compon->diffuse = xe_render::get_texture2D_resource("albedo_iron");

        xe_ecs::transform_component *trans_component = new xe_ecs::transform_component();
        trans_component->set_translation(0.0f, -4.0f, -5.0f);
        trans_component->set_scale(4.0f, 4.0f, 4.0f);

        sphere_entity->add_component(sphere_compon);
        sphere_entity->add_component(trans_component);

        sc->entities.push_back(sphere_entity);
    }
}
