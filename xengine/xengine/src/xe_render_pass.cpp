#include "xe_render_pass.h"
#include "xe_render.h"
#include "xe_assets.h"
#include "xe_input.h"

using namespace xe_ecs;

void xe_graphics::render_pass2D::init()
{
    graphics_device *device = xe_render::get_device();

    device->create_texture2D("engineassets/get.png", &result_texture);
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
    device->set_int("texture_diff", 0, simple_shader);
}

void xe_graphics::render_pass2D::clear()
{
    graphics_device *device = xe_render::get_device();

    device->destroy_texture2D(&result_texture);
}

void xe_graphics::render_pass2D::load_resources()
{

}

void xe_graphics::render_pass2D::unload_resources()
{

}

void xe_graphics::render_pass2D::render()
{     
    quad_component* mesh = main_ent.find_component<quad_component>();
    transform_component *tr = main_ent.find_component<transform_component>();

    glm::vec3 pos = tr->position;
    glm::vec3 sc = tr->scale;

    glm::mat4 model_matrix = glm::mat4(1.0f);

    model_matrix = glm::translate(model_matrix, pos);
    model_matrix = glm::scale(model_matrix, sc);

    xe_render::draw_quad(mesh->quad_mesh, simple_shader, &result_texture, model_matrix, &camera2D);
}

void xe_graphics::render_pass2D::update(float dt)
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
    device->set_vec3("color", glm::vec3(1.0f, 0.0f, 0.0f), color_shader);

    ent.add_component(new mesh_component());
    ent.add_component(new transform_component());

    mesh_component *mesh = ent.find_component<mesh_component>();
    mesh->model_asset = xe_assets::load_model_from_file("engineassets/nano/nanosuit.obj");

    mesh_component *cube = new mesh_component();
    cube->model_asset = xe_assets::load_model_from_file("engineassets/cube.obj");

    dir_light *dl = new dir_light();
    dl->color = glm::vec3(0.8f, 0.7f, 0.8f);
    dl->entensity = 0.9f;   

    transform_component *light_transform = new transform_component();
    light_transform->position = glm::vec3(3.0f, 1.0f, 150.0f);

    light_ent.add_component(dl);
    light_ent.add_component(light_transform);
    light_ent.add_component(cube);

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

void xe_graphics::render_pass3D::load_resources()
{

}

void xe_graphics::render_pass3D::unload_resources()
{

}

void xe_graphics::render_pass3D::render()
{
    XEngine::PerspectiveCamera cam = get_camera3d();

    dir_light *light = light_ent.find_component<dir_light>();
    transform_component *transform = light_ent.find_component<transform_component>();

    mesh_component *mesh_light = light_ent.find_component<mesh_component>();
    shader *color_shader = xe_render::get_color_shader();
    
    graphics_device *device = xe_render::get_device();

    device->bind_framebuffer(&fbo);
    device->clear_color(0.0f, 0.0f, 0.0f, 1.0f);
    device->clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if (mesh_light != nullptr)
        xe_render::draw_model(mesh_light->model_asset, color_shader, &cam);

    mesh_component *model_mesh = ent.find_component<mesh_component>();
    shader *model_shader = xe_render::get_model_shader();

    if (light)
        xe_render::apply_dir_light(model_shader, light, transform);

    xe_render::draw_model(model_mesh->model_asset, model_shader, &cam);
   
    device->unbind_framebuffer();
}

void xe_graphics::render_pass3D::update(float dt)
{
    float speed = 12.0f;

    if (xe_input::pressed(xe_input::KEYBOARD_W))
    {
        camera3D.camPos -= speed * dt * glm::vec3(0.0f, 0.0f, 1.0f);
    }

    if (xe_input::pressed(xe_input::KEYBOARD_S))
    {
        camera3D.camPos += speed * dt * glm::vec3(0.0f, 0.0f, 1.0f);
    }

    if (xe_input::pressed(xe_input::KEYBOARD_A))
    {
        camera3D.camPos -= speed * dt * glm::vec3(1.0f, 0.0f, 0.0f);
    }

    if (xe_input::pressed(xe_input::KEYBOARD_D))
    {
        camera3D.camPos += speed * dt * glm::vec3(1.0f, 0.0f, 0.0f);
    }

    if (xe_input::pressed(xe_input::KEYBOARD_V))
    {
        transform_component *tr = light_ent.find_component<transform_component>();
        tr->position.x += 0.8f * sin(dt);
        tr->position.z += 0.8f * cos(dt);
    }

    if (xe_input::pressed(xe_input::KEYBOARD_B))
    {
        transform_component *tr = light_ent.find_component<transform_component>();
        tr->position.x -= 0.8f * sin(dt);
        tr->position.z -= 0.8f * cos(dt);
    }

    transform_component *light_transform = light_ent.find_component<transform_component>();

    if (light_transform)
    {
        //light_transform->position.x += 2.2f * sin(dt);
        //light_transform->position.z += 2.2f * cos(dt);
    }        
}

void xe_graphics::gamma_correction_pass::init()
{
    graphics_device *device = xe_render::get_device();
    gmshd = xe_render::get_gamma_correction_shader();
}

void xe_graphics::gamma_correction_pass::clear()
{

}

void xe_graphics::gamma_correction_pass::load_resources()
{

}

void xe_graphics::gamma_correction_pass::unload_resources()
{

}

void xe_graphics::gamma_correction_pass::render()
{
    graphics_device *device = xe_render::get_device();

    if(texture != nullptr)
        device->activate_bind_texture2d(texture);

    device->bind_shader(gmshd);
    device->set_int("tex_diff", 0, gmshd);
    
    xe_render::draw_full_quad();

    device->unbind_texture2d();
    device->unbind_shader();
}

void xe_graphics::gamma_correction_pass::update(float dt)
{

}
