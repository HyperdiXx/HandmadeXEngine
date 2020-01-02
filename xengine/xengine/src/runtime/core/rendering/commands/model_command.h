#pragma once

#ifndef MODEL_COMMAND_H
#define MODEL_COMMAND_H

#include "rendercommand.h"

namespace XEngine
{
    namespace Rendering
    {
        class ModelRenderCommand : public RenderCommand
        {
        public:
            ModelRenderCommand(std::string name, RenderCommandType type) : m_name(name), m_type(type) {}
            
            virtual void execute()
            {
                int a = 1234;
                int b = a * 2;
                int c = b;
            };

            inline std::string get_name() const { return m_name; }
            
        private:
            std::string m_name;
            RenderCommandType m_type;
        };
    }
}
#endif // !MODEL_COMMAND_H

