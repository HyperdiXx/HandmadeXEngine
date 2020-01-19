#include "render.h"

#include "glrender.h"


#include <runtime/core/utility/log.h>

namespace XEngine
{
    namespace Rendering
    {
        void Render::start_execution()
        {
            // TODO : setup

            // @move to GL Render device abst and setup here
            glEnable(GL_DEPTH_TEST);
        }

        void Render::end_execution()
        {
            for (int i = 0; i < m_commands.size(); ++i)
            {
                RenderCommand* command = m_commands[i];
                command->execute();
                
                // clearing command here. Mb better way
                delete command;
            }

            m_commands.clear();

            glDisable(GL_DEPTH_TEST);
        }

        void Render::add(RenderCommand *command)
        {
            // Assert not null
            m_commands.push_back(command);
        }

        Render *Render::create()
        {
            switch (Render::get_api())
            {
            case APIs::RenderAPI::API::OpenGL: 
                return new GLRender();
                break;
            default:
                Log::info("Unsupported API!!!");
                break;
            }

            return nullptr;
        }
    }
}