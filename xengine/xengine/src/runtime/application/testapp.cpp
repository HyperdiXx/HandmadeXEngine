#include "testapp.h"

#include <runtime/core/rendering/api/base/texture2d.h>
#include <runtime/core/rendering/api/base/vertexbuffer.h>
#include <runtime/core/rendering/api/base/indexbuffer.h>
#include <runtime/core/rendering/api/base/vertexarray.h>
#include <runtime/core/rendering/api/base/shader.h>
#include <runtime/core/windowsystem/openglwindow.h>

#include <runtime/core/rendering/render/render.h>

#include <runtime/core/geometry/model.h>

namespace XEngine
{
    TestApp::TestApp()
    {
        window = new GLWindow("Game", 1280, 720);

        render_instance = Rendering::Render::create();

        //triangle_shader = Rendering::Shader::create("shaders/simple2d.vs", "shaders/simple2d.fs");

        texture1 = Rendering::Texture2D::create("engineassets/brickwall.jpg");       
        
        model = new Assets::Model("engineassets/nano/nanosuit.obj", false);
        
        real32 vertices_color[] =
        {
             0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   
             0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   
            -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   
            -0.5f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f   
        };

        real32 vertices[] =
        {
              0.5f,  0.5f, 0.0f,   1.0f, 1.0f,
              0.5f, -0.5f, 0.0f,   1.0f, 0.0f,
             -0.5f, -0.5f, 0.0f,   0.0f, 0.0f,
             -0.5f,  0.5f, 0.0f,   0.0f, 1.0f
        };

        unsigned int indices[] =
        {
           0, 1, 3,
           1, 2, 3
        };

        /*v_array = Rendering::VertexArray::create();

        v_buffer = Rendering::VertexBuffer::create(vertices, 20);
        i_buffer = Rendering::IndexBuffer::create(indices, 6);

        Rendering::BufferLayout buffer_layout = 
        {
            { "aPos", Rendering::ElementType::Float3  },
            { "aUV",  Rendering::ElementType::Float2, }
        };

        v_buffer->set_layout(buffer_layout);

        v_array->add_vertex_buffer(v_buffer);
        v_array->set_index_buffer(i_buffer);

        //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        //glEnableVertexAttribArray(0);

        //glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        //glEnableVertexAttribArray(1);

        triangle_shader->bind();
        triangle_shader->setInt("textureDiffuse", 0);*/
    }

    TestApp::~TestApp()
    {
        window->destroy();
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

        //render_instance->start_execution();

        //texture1->bind(0);
        //triangle_shader->bind();

        //v_array->bind();
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        //v_array->unbind();

        //render_instance->draw_quad();

        //render_instance->draw_model(model);

        //render_instance->draw_quad();
        
        //render_instance->end_execution();
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
        glfwTerminate();
    }
}
