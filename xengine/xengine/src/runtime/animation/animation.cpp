#include "animation.h"

#include <runtime/animation/key_frame.h>

namespace XEngine
{
    void Animation::set_name(std::string name)
    {
        m_name = name;
    }

    void Animation::set_time(double rate)
    {
        m_anim_time = rate;
    }

    void Animation::set_duration(double dur)
    {
        m_duration = dur;
    }

    void Animation::add_keyframe(KeyFrame *keyframe)
    {
        m_key_map[keyframe->name] = m_key_frames.size();
        m_key_frames.emplace_back(keyframe);
    }
}
