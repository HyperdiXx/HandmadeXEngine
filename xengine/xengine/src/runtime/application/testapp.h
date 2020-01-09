#pragma once

#ifndef TESTAPP_H
#define TESTAPP_H

#include "baseapp.h"

#include <runtime/core/ecs/entity.h>

namespace XEngine
{
    class GLWindow;

    namespace Geometry
    {
        class Quad;
    }

    namespace Assets
    {
        class Model;
    }

    namespace Rendering
    {
        class Shader;
        class Texture2D;
        class VertexBuffer;
        class IndexBuffer;
        class VertexArray;
        class Render;
    }

    class TestApp : public BaseApplication
    {
    public:
        TestApp();
        ~TestApp();

        void run();

        void onUpdate(float dt);
        void onDraw();       
        void onPostUpdate();
        void onShutdown();

    private:
        XEngine::GLWindow *window = nullptr;

        Entity m_entity;

        Rendering::Shader *triangle_shader = nullptr;
        Rendering::Texture2D *texture1 = nullptr;
        Rendering::VertexBuffer *v_buffer = nullptr;
        Rendering::IndexBuffer *i_buffer = nullptr;
        Rendering::VertexArray *v_array = nullptr;
        Rendering::Render *render_instance = nullptr;
        Assets::Model *model = nullptr;
        Geometry::Quad *quad = nullptr;
    };
}
#endif // !TESTAPP_H
