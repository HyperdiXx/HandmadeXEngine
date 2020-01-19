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

        virtual void onUpdate(float dt) override;
        virtual void onDraw() override;       
        virtual void onPostUpdate() override;
        virtual void onShutdown() override;

    private:
        XEngine::GLWindow *window = nullptr;
        Rendering::Render *render_instance = nullptr;

        Entity m_entity;

        Rendering::Shader *triangle_shader = nullptr;
        Rendering::Texture2D *texture1 = nullptr;
        Rendering::VertexBuffer *v_buffer = nullptr;
        Rendering::IndexBuffer *i_buffer = nullptr;
        Rendering::VertexArray *v_array = nullptr;
        Rendering::Shader *model_shader = nullptr;

        glm::mat4 model_matrix = glm::mat4(1.0f);

        Assets::Model *model = nullptr;
        Geometry::Quad *quad = nullptr;
    };
}
#endif // !TESTAPP_H
