#pragma once

#ifndef RENDERABLE_H
#define RENDERABLE_H

#include "component.h"

#include <runtime/core/rendering/api/base/texture2d.h>
#include <runtime/core/rendering/api/base/shader.h>

namespace XEngine
{
    class Renderable : public Component
    {
    public:
        virtual void draw() {};
    private:
        Rendering::Shader *m_shader = nullptr;
        Rendering::Texture2D *m_texture = nullptr;
    };
}
#endif // !RENDERABLE_H


