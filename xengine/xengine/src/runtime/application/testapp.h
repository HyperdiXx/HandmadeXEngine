#pragma once

#ifndef TESTAPP_H
#define TESTAPP_H

#include "baseapp.h"

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
        class BasicMaterial;
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
        Rendering::Shader *triangle_shader = nullptr;
        Rendering::Texture2D *texture1 = nullptr;
        Rendering::VertexBuffer *v_buffer = nullptr;
        Rendering::IndexBuffer *i_buffer = nullptr;
        Rendering::VertexArray *v_array = nullptr;
        Rendering::Shader *model_shader = nullptr;
        Rendering::Shader *solid_shader = nullptr;
        Rendering::Shader *skeletal_shader = nullptr;
        Rendering::BasicMaterial *base_material = nullptr;
        Assets::Model *model = nullptr;
        Geometry::Quad *quad = nullptr;
    };
}
#endif // !TESTAPP_H
