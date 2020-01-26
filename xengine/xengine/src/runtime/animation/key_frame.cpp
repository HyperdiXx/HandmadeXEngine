#include "key_frame.h"

namespace XEngine
{
    void KeyFrame::add_position_key(PositionKey k)
    {
        positions.push_back(k);
    }

    void KeyFrame::add_rotation_key(RotationKey k)
    {
        rotations.push_back(k);
    }

    void KeyFrame::add_scale_key(PositionKey k)
    {
        scales.push_back(k);
    }

    inline PositionKey& KeyFrame::get_position_key(int index)
    {
        if(index >= 0 && index <= positions.size() - 1)
            return positions[index];
    }

    inline RotationKey& KeyFrame::get_rotation_key(int index)
    {
        if (index >= 0 && index <= positions.size() - 1)
            return rotations[index];
    }

    inline PositionKey& KeyFrame::get_scale_key(int index)
    {
        if (index >= 0 && index <= positions.size() - 1)
            return scales[index];
    }
}
