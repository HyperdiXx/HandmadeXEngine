#include "xe_render_pass.h"
#include "xe_render.h"
#include "xe_assets.h"
#include "xe_input.h"
#include "config.h"

#include "xe_scene.h"

using namespace xe_ecs;

void xe_graphics::render_pass2D::init()
{
    graphics_device *device = xe_render::get_device();

    device->create_texture2D("assets/get.png", &result_texture);
    simple_shader = xe_render::get_simple_shader();

    main_ent.add_component(new quad_component());
    main_ent.add_component(new transform_component());
    main_ent.add_component(new update_component());

    quad_component* mesh = main_ent.find_component<quad_component>();
    transform_component *transform = main_ent.find_component<transform_component>();

    transform->position = glm::vec3(200.0f, 200.0f, 0.0f);
    transform->scale = glm::vec3(100.0f, 100.0f, 100.0f);

    mesh->quad_mesh = new quad();
    xe_render::create_quad(mesh->quad_mesh);

    device->bind_shader(simple_shader);
    device->set_int("tex_diff", 0, simple_shader);
}

void xe_graphics::render_pass2D::clear()
{
    graphics_device *device = xe_render::get_device();

    device->destroy_texture2D(&result_texture);
}

void xe_graphics::render_pass2D::unload_resources()
{

}

void xe_graphics::render_pass2D::render()
{ 
    using namespace xe_render;

    draw_quad(&main_ent, simple_shader, &result_texture, &camera2D);
    draw_text(ENGINE_NAME, 10, 10);     
}

void xe_graphics::render_pass2D::update(real32 dt)
{
    update_component *updater = main_ent.find_component<update_component>();

    if (!updater)
        return;

    transform_component *transform = main_ent.find_component<transform_component>();
    
    transform->position += glm::vec3(0.0f, 1.0f, 0.0f) * dt * 12.f;
    transform->scale += glm::vec3(1.0f, 1.0f, 0.0f) * dt * 12.f;

    if (transform->position.y >= 720)
        transform->position.y = 0;
    if (transform->scale.x >= 200.0f || transform->scale.y >= 200.0f)
    {
        transform->scale.x = 100.f;
        transform->scale.y = 100.f;
    }
}

void xe_graphics::render_pass3D::init()
{
    graphics_device *device = xe_render::get_device();
    
    shader *model_shader = xe_render::get_model_shader();
    shader *color_shader = xe_render::get_color_shader();

    device->bind_shader(model_shader);
    device->set_int("tex_diff", 0, model_shader);

    device->bind_shader(color_shader);
    device->set_vec3("color", glm::vec3(0.5f, 0.9f, 0.9f), color_shader);

    /*mesh_component *mesh = new mesh_component();
    mesh->model_asset = xe_assets::load_model_from_file("assets/nano/nanosuit.obj");
    
    transform_component *nano_transform = new transform_component();
    nano_transform->position = glm::vec3(-20.0f, -9.0f, -50.0f);

    ent.add_component(mesh);
    ent.add_component(nano_transform);*/
 
    /*mesh_component *cube = new mesh_component();
    cube->model_asset = xe_assets::load_model_from_file("assets/cube.obj");

    dir_light *dl = new dir_light();
    dl->color = glm::vec3(0.8f, 0.7f, 0.8f);
    dl->entensity = 0.9f;   

    transform_component *light_transform = new transform_component();
    light_transform->position = glm::vec3(3.0f, 1.0f, -10.0f);
    
    light_ent.add_component(dl);
    light_ent.add_component(light_transform);
    light_ent.add_component(cube);*/

    device->create_texture2D(1280, 720, &color_texture);
   
    device->create_framebuffer(1, &fbo);  
    device->bind_framebuffer(&fbo);
    device->bind_for_write(&fbo);
    device->create_render_buffer(1, &fbo);

    device->add_color_texture2D(&color_texture, 0, &fbo);
    device->add_depth_texture2D(1280, 720, &fbo);

    device->check_framebuffer();
    device->unbind_framebuffer();

    // init ents

    //ents.reserve(16);

    /*for (int i = 0; i < 10; ++i)
    {
        entity *entity_add = new entity();
        transform_component *transform = new transform_component();
        transform->position = glm::vec3(30.0f * (i - 5), 0.0f, -5.0f * (i + 1));
        transform->scale = glm::vec3(0.2f, 0.2f, 0.2f);

        mesh_component *loading_model = new mesh_component();
        loading_model->model_asset = xe_assets::load_model_from_file("assets/cube.obj");

        entity_add->add_component(transform);
        entity_add->add_component(loading_model);

        ents.push_back(entity_add);
    }*/

    /*mesh_component *plane_mesh = new mesh_component();
    plane_mesh->model_asset = xe_assets::load_model_from_file("assets/cube.obj");
    transform_component *transform_plane = new transform_component();
    transform_plane->position = glm::vec3(3.0f, -10.0f, 25.0f);
    transform_plane->scale = glm::vec3(10.0f, 0.001f, 10.0f);

    plane_ent.add_component(plane_mesh);
    plane_ent.add_component(transform_plane);*/
}

void xe_graphics::render_pass3D::clear()
{

}

void xe_graphics::render_pass3D::unload_resources()
{

}

void xe_graphics::render_pass3D::render()
{
    graphics_device *device = xe_render::get_device();
    XEngine::PerspectiveCamera* cam = get_camera3d();

    shader *color_shader = xe_render::get_color_shader();
    shader *model_shader = xe_render::get_model_shader();

    viewport vp = device->get_viewport();

    device->bind_framebuffer(&fbo);
    device->set_viewport(0, 0, 1280, 720);
    device->clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    device->enable(GL_DEPTH_TEST);
    device->enable(GL_CULL_FACE);
    device->set_cull_mode(GL_BACK);

    for (uint16 i = 0; i < current_scene->entities.size(); ++i)
    {
        entity *current_ent = current_scene->entities[i];
        
        dir_light *light = current_ent->find_component<dir_light>();
        transform_component *transform = current_ent->find_component<transform_component>();

        if(light)
            xe_render::apply_dir_light(model_shader, light, transform);

        xe_render::draw_ent(current_ent, cam);
    }

    device->disable(GL_CULL_FACE);

    xe_render::draw_skybox(cam);

    device->disable(GL_DEPTH_TEST);
    device->unbind_framebuffer();

    device->set_viewport(0, 0, vp.width, vp.height);
}

void xe_graphics::render_pass3D::update(real32 dt)
{
    float speed = 12.0f;

    if (xe_input::pressed(xe_input::KEYBOARD_W))
    {
        camera3D->camPos -= speed * dt * glm::vec3(0.0f, 0.0f, 1.0f);
    }

    if (xe_input::pressed(xe_input::KEYBOARD_S))
    {
        camera3D->camPos += speed * dt * glm::vec3(0.0f, 0.0f, 1.0f);
    }

    if (xe_input::pressed(xe_input::KEYBOARD_A))
    {
        camera3D->camPos -= speed * dt * glm::vec3(1.0f, 0.0f, 0.0f);
    }

    if (xe_input::pressed(xe_input::KEYBOARD_D))
    {
        camera3D->camPos += speed * dt * glm::vec3(1.0f, 0.0f, 0.0f);
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
   
    //transform_component *light_transform = light_ent.find_component<transform_component>();

    //if (light_transform)
   // {
        //light_transform->position.x += 2.2f * sin(dt);
        //light_transform->position.z += 2.2f * cos(dt);
    //}        
}

void xe_graphics::gamma_correction_pass::init()
{
    graphics_device *device = xe_render::get_device();
    gmshd = xe_render::get_gamma_correction_shader();
}

void xe_graphics::gamma_correction_pass::clear()
{

}

void xe_graphics::gamma_correction_pass::unload_resources()
{

}

void xe_graphics::gamma_correction_pass::render()
{
    graphics_device *device = xe_render::get_device();

    if(texture != nullptr)
        device->activate_bind_texture(TEXTURE_TYPE::COLOR, texture);

    device->bind_shader(gmshd);
    device->set_int("tex_diff", 0, gmshd);
    
    xe_render::draw_full_quad();

    device->unbind_texture(TEXTURE_TYPE::COLOR);
    device->unbind_shader();
}

void xe_graphics::gamma_correction_pass::update(real32 dt)
{

}

void xe_graphics::shadow_map_pass::init()
{
    // @Refactor: initialization here
    shadow = new shadow_map();

    bool32 shadow_map_inited = xe_render::create_shadow_maps(shadow);

    if (!shadow_map_inited)
        printf("Failed to create shadow map!\n");
   
    graphics_device *device = xe_render::get_device();

    shader *depth_shader = xe_render::get_shadow_map_depth_shader();
    shader *shadow_map_shader = xe_render::get_shadow_map_shader();

    device->bind_shader(shadow_map_shader);
    device->set_int("diff_tex", 0, shadow_map_shader);
    device->set_int("shadow_map", 1, shadow_map_shader);
}

void xe_graphics::shadow_map_pass::clear()
{

}

void xe_graphics::shadow_map_pass::unload_resources()
{

}

void xe_graphics::shadow_map_pass::render()
{
    graphics_device *device = xe_render::get_device();
    XEngine::PerspectiveCamera* cam = get_camera3d();

    device->set_viewport(0, 0, shadow->w, shadow->h);
    device->bind_framebuffer(&shadow->depth_fbo);
    device->clear(GL_DEPTH_BUFFER_BIT);

    xe_render::apply_shadow_map(shadow);

    for (uint16 i = 0; i < current_scene->entities.size(); ++i)
    {
        entity *current_ent = current_scene->entities[i];

        xe_render::draw_ent(current_ent, cam);
    }
        
    //RenderScene();
    
    device->unbind_framebuffer();
}

void xe_graphics::shadow_map_pass::update(real32 dt)
{

}

void xe_graphics::shadow_map_pass::bind_depth_texture() const
{
    graphics_device *device = xe_render::get_device();

    device->bind_texture(TEXTURE_TYPE::DEPTH, shadow->depth_fbo.depth_texture);

}
