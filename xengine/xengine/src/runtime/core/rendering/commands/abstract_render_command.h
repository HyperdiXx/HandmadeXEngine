#pragma once

#ifndef ABSTRACT_RENDER_COMMAND_H
#define ABSTRACT_RENDER_COMMAND_H

namespace XEngine
{
    namespace Rendering
    {
        enum class RenderCommandType
        {
            NONE,
            MODEL,
            TEXT,
            QUAD,
            ANIMATED,
            SPECIAL
        };

        //class AbstractRenderCommand
        //{
        //public:
        //    virtual void execute() = 0;           
        //};
    }
}
#endif // !ABSTRACT_RENDER_COMMAND_H


