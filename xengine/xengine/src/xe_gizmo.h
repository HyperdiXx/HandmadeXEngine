#pragma once

#ifndef XE_GIZMO_H
#define XE_GIZMO_H

#include "types.h"

#include <glm/glm.hpp>

namespace xe_gizmo
{
    struct Config
    {
        enum Mode 
        {
            TRANSLATE,
            ROTATE,
            SCALE
        } mode = TRANSLATE;

        enum CoordSystem
        {
            GLOBAL,
            LOCAL
        } coord_system = GLOBAL;

        bool32 autosnap = false;
        real32 steps[3] = {};
        bool32 is_step = false;
        glm::vec3 offset = {};
        real32 scale = 1.f;

        bool32 isTranslateMode() const { return mode == TRANSLATE; }
        bool32 isRotateMode() const { return mode == ROTATE; }
        bool32 isScaleMode() const { return mode == SCALE; }
        
        bool32 isLocalCoordSystem() const { return coord_system == LOCAL; }
        bool32 isGlobalCoordSystem() const { return coord_system == GLOBAL; }
       
        bool32 isAutosnapDown() const { return autosnap; }
        void setAutosnapDown(bool value) { autosnap = value; }
        
        real32 getStep() const { return steps[mode]; }
        
        void setStep(real32 step) { steps[mode] = step; }
        
        void enableStep(bool32 enable) { is_step = enable; }
        
        glm::vec3 getOffset() const { return offset; }
        
        void setOffset(const glm::vec3& val) { offset = val; }
    };

    void initGizmo(Config &cfg);    
    void updateGizmo();
    void manipulateGizmo();
}
#endif // !XE_GIZMO_H

