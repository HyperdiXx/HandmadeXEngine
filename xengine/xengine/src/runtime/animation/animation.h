#pragma once

#ifndef ANIMATION_H
#define ANIMATION_H

#include <xenpch.h>

namespace XEngine
{
    namespace Assets
    {
        class Animation
        {
        public:

            void set_name(std::string name);
            void set_time();

            inline std::string get_name() { return m_name; }

        private:
            double anim_time = 0.0;
            
            int start_time = 0;            
            int end_time;

            bool is_playing;
            bool is_loop;
           
            std::string m_name;
        };
    }
}

#endif // !ANIMATION_H

