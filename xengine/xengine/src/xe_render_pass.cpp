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

    simple_shader = xe_render::get_shader("simple2d");

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
    
    shader *model_shader = xe_render::get_shader("base3d");
    shader *color_shader = xe_render::get_shader("color");

    device->bind_shader(model_shader);
    device->set_int("tex_diff", 0, model_shader);

    device->bind_shader(color_shader);
    device->set_vec3("color", glm::vec3(0.5f, 0.9f, 0.9f), color_shader);

    device->create_texture2D(1280, 720, &color_texture);
   
    device->create_framebuffer(1, &fbo);  
    device->bind_framebuffer(&fbo);
    device->bind_for_write(&fbo);
    device->create_render_buffer(1, &fbo);

    device->add_color_texture2D(&color_texture, 0, &fbo);
    device->add_depth_texture2D(1280, 720, &fbo);

    device->check_framebuffer();
    device->unbind_framebuffer();
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
    
    shader *color_shader = xe_render::get_shader("color");
    shader *model_shader = xe_render::get_shader("base3d");
     
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
        
        xe_render::draw_ent(current_ent);
    }

    device->disable(GL_CULL_FACE);

    xe_render::draw_skybox();

    device->disable(GL_DEPTH_TEST);
    device->unbind_framebuffer();

    device->set_viewport(0, 0, vp.width, vp.height);
}

void xe_graphics::render_pass3D::update(real32 dt)
{
    xe_ecs::camera3d_component& camera3D = xe_render::get_camera3D();
    
    if (xe_input::pressed(xe_input::KEYBOARD_W))
    {
        camera3D.pos -= camera3D.speed * dt * glm::vec3(0.0f, 0.0f, 1.0f);
    }

    if (xe_input::pressed(xe_input::KEYBOARD_S))
    {
        camera3D.pos += camera3D.speed * dt * glm::vec3(0.0f, 0.0f, 1.0f);
    }

    if (xe_input::pressed(xe_input::KEYBOARD_A))
    {
        camera3D.pos -= camera3D.speed * dt * glm::vec3(1.0f, 0.0f, 0.0f);
    }

    if (xe_input::pressed(xe_input::KEYBOARD_D))
    {
        camera3D.pos += camera3D.speed * dt * glm::vec3(1.0f, 0.0f, 0.0f);
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
    
    xe_ecs::entity *light_ent = current_scene->directional_light;
    transform_component *light_transform = light_ent->find_component<transform_component>();

    if (light_transform)
    {
        glm::vec3 &pos = light_transform->position;
        light_transform->set_translation(pos.x + 12.2f * dt, pos.y, pos.z + 12.2f * dt);
    }
}

void xe_graphics::gamma_correction_pass::init()
{
    graphics_device *device = xe_render::get_device();
    gmshd = xe_render::get_shader("gc");
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

    shader *depth_shader = xe_render::get_shader("shadow_depth");
    shader *shadow_map_shader = xe_render::get_shader("shadow_map");

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
    
    device->set_viewport(0, 0, shadow->w, shadow->h);
    device->bind_framebuffer(&shadow->depth_fbo);
    device->clear(GL_DEPTH_BUFFER_BIT);

    xe_render::apply_shadow_map(shadow);

    glm::mat4 light_view_matrix = glm::lookAt(light_pos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
    glm::mat4 light_space_matrix = light_view_matrix * shadow->light_projection_matrix;
  
    shader *depth_shader = xe_render::get_shader("shadow_depth");
    device->bind_shader(depth_shader);
    device->set_mat4("light_space_matrix", light_space_matrix, depth_shader);

    for (uint16 i = 0; i < current_scene->entities.size(); ++i)
    {
        entity *current_ent = current_scene->entities[i];

        xe_render::draw_ent_with_shader(current_ent, depth_shader);
    }
        
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
