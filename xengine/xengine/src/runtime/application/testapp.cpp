#include "testapp.h"

#include <runtime/core/rendering/api/base/texture2d.h>
#include <runtime/core/rendering/api/base/vertexbuffer.h>
#include <runtime/core/rendering/api/base/indexbuffer.h>
#include <runtime/core/rendering/api/base/vertexarray.h>
#include <runtime/core/rendering/api/base/shader.h>
#include <runtime/core/windowsystem/openglwindow.h>

#include <runtime/core/rendering/render/render.h>

#include <runtime/core/geometry/model.h>
#include <runtime/core/geometry/quad.h>

namespace XEngine
{
    TestApp::TestApp()
    {
        window = new GLWindow("Game", 1280, 720);

        render_instance = Rendering::Render::create();

        triangle_shader = render_instance->create_shader("shaders/simple2d.vs", "shaders/simple2d.fs");
        texture1 = render_instance->create_texture2D("engineassets/brickwall.jpg");

        model = new Assets::Model("engineassets/nano/nanosuit.obj", false);        
       
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
        
        render_instance->clear_color(0.0f, 1.0f, 0.0f, 1.0f);
        render_instance->clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        render_instance->start_execution();

        // Texture bind here, cause not setupped in command
        texture1->bind(0);        
        render_instance->draw_quad(quad, triangle_shader);

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
