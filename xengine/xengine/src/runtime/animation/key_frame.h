#pragma once

#ifndef KEY_FRAME_H
#define KEY_FRAME_H

#include <xenpch.h>

namespace XEngine
{
    struct PositionKey
    {
        double time;
        glm::vec3 value;
    };

    struct RotationKey
    {
        double time;
        glm::quat value;
    };

    class KeyFrame
    {
    public:
        void add_position_key(PositionKey k);
        void add_rotation_key(RotationKey k);
        void add_scale_key(PositionKey k);
        
        inline PositionKey& get_position_key(int index);
        inline RotationKey& get_rotation_key(int index);
        inline PositionKey& get_scale_key(int index);
    
    public:
        std::string name;
    
    private:
        std::vector<PositionKey> positions;
        std::vector<RotationKey> rotations;
        std::vector<PositionKey> scales;

    };
}
#endif // !KEY_FRAME_H

