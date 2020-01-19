#include "testapp.h"

#include <runtime/core/rendering/api/base/texture2d.h>
#include <runtime/core/rendering/api/base/vertexbuffer.h>
#include <runtime/core/rendering/api/base/indexbuffer.h>
#include <runtime/core/rendering/api/base/vertexarray.h>
#include <runtime/core/rendering/api/base/shader.h>
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
        
        model_shader = render_instance->create_shader("shaders/model3d.vs", "shaders/model3d.fs");

        texture1 = render_instance->create_texture2D("engineassets/brickwall.jpg");

        model = ModelLoader::load_model_from_file("engineassets/nano/nanosuit.obj");
        
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
       
        //model_matrix = glm::rotate(model_matrix, glm::radians(15.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model_matrix = glm::translate(model_matrix, glm::vec3(0.0f, -10.0f, -30.0f));
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
        
        render_instance->end_execution();
    }

    void TestApp::onUpdate(float dt)
    {

    }

    void TestApp::onPostUpdate()
    {
        window->update();
    }


    void TestApp::onShutdown()
    {
        window->destroy();
    }
}
