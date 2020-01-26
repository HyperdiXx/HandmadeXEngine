#pragma once

#ifndef ANIMATION_H
#define ANIMATION_H

#include <xenpch.h>

namespace XEngine
{
    class KeyFrame;

    class Animation
    {
    public:

        void set_name(std::string name);
        void set_time(double rate);
        void set_duration(double dur);

        void add_keyframe(KeyFrame *keyframe);

        void get_interpolated_pos(double t);

        inline std::string get_name() { return m_name; }

    private:
        double m_anim_time = 0.0;
        double m_duration = 0.0;

        int m_start_time = 0;
        int m_end_time;

        bool m_is_playing;
        bool m_is_loop;

        std::string m_name;

        std::unordered_map<std::string, size_t> m_key_map;
        std::vector<KeyFrame*> m_key_frames;
    };
}

#endif // !ANIMATION_H

