#include "xe_render_pass.h"
#include "xe_render.h"
#include "xe_assets.h"

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

    transform->position = glm::vec3(300.0f, 200.0f, 0.0f);
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

    //transform_component *transform = main_ent.find_component<transform_component>();
    

}

void xe_graphics::render_pass3D::init()
{
    graphics_device *device = xe_render::get_device();
    
    model_shader = xe_render::get_model_shader();

    device->bind_shader(model_shader);
    device->set_int("tex_diff", 0, model_shader);

    ent.add_component(new mesh_component());
    ent.add_component(new transform_component());

    mesh_component *mesh = ent.find_component<mesh_component>();
    //mesh->model_asset = xe_assets::load_model_from_file("engineassets/nano/nanosuit.obj");
    model = xe_assets::load_model_from_file("engineassets/nano/nanosuit.obj");


    //model_matrix = glm::rotate(model_matrix, glm::radians(15.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    //model_matrix = glm::translate(model_matrix, glm::vec3(0.0f, -10.0f, -20.0f));
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
    graphics_device *device = xe_render::get_device(); 
    XEngine::PerspectiveCamera cam = get_camera3d();
    xe_render::draw_model(model, model_shader, &cam);
}

void xe_graphics::render_pass3D::update(float dt)
{
}
