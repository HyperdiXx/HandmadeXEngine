#include "testapp.h"

#include <runtime/core/rendering/pipeline/materials/basicmaterial.h>
#include <runtime/core/rendering/api/base/vertexbuffer.h>
#include <runtime/core/rendering/api/base/indexbuffer.h>
#include <runtime/core/rendering/api/base/vertexarray.h>
#include <runtime/core/windowsystem/openglwindow.h>

#include <runtime/core/rendering/render/render.h>

#include <runtime/geometry/model.h>
#include <runtime/geometry/quad.h>
#include <runtime/geometry/model_loader.h>


namespace XEngine
{
    TestApp::TestApp()
    {
        window = new GLWindow("Game", 1280, 720);

        render_instance = Rendering::Render::create();
        using namespace Rendering;

        triangle_shader = render_instance->create_shader("shaders/simple2d.vs", "shaders/simple2d.fs");
        //solid_shader = render_instance->create_shader("shaders/simple2d.vs", "shaders/filledsimple2d.fs");
        model_shader = render_instance->create_shader("shaders/model3d.vs", "shaders/model3d.fs");
        skeletal_shader = render_instance->create_shader("shaders/skeletal.vs", "shaders/model3d.fs");

        texture1 = render_instance->create_texture2D("engineassets/brickwall.jpg");

        base_material = new Rendering::BasicMaterial();

        base_material->set_texture2D(texture1);
        base_material->set_shader(triangle_shader);

        model = ModelLoader::load_model_from_file("engineassets/nano/nanosuit.obj");
        
        m_ui.init(window->get_wind_ptr(), 1);

        // @Test
        real32 vertices_color[] =
        {
             0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   
             0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   
            -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   
            -0.5f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f   
        };

        quad = new Geometry::Quad(vec3f(0.0f, 0.0f, 0.0f));

        triangle_shader->bind();
        triangle_shader->setInt("textureDiffuse", 0);

        model_shader->bind();
        model_shader->setInt("tex_diff", 0);
       
        model_matrix = glm::rotate(model_matrix, glm::radians(15.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model_matrix = glm::translate(model_matrix, glm::vec3(0.0f, -10.0f, -20.0f));
    }

    TestApp::~TestApp()
    {
        
    }

    void TestApp::run()
    {
        while (!window->isClosed())
        {
            onUpdate(1.0f);
            onDraw();
            onPostUpdate();
        }
    }

    void TestApp::onDraw()
    {
        using namespace Rendering;        
        
        render_instance->clear_color(0.9f, 0.9f, 0.9f, 1.0f);
        render_instance->clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        render_instance->start_execution();
       
        render_instance->draw_model(model, model_shader, model_matrix);
        
        //render_instance->draw_quad(quad, base_material);
        
        render_instance->end_execution();

        m_ui.new_frame();
        m_ui.top_bar();

    }

    void TestApp::onUpdate(float dt)
    {

    }

    void TestApp::onPostUpdate()
    {
        m_ui.post_update();
        window->update();
    }


    void TestApp::onShutdown()
    {
        m_ui.shutdown();
        window->destroy();
    }
}
