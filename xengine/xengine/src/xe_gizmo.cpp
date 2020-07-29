#include "xe_gizmo.h"

#include "xe_render.h"

#include "xe_math.h"

#include "xe_utility.h"

namespace xe_gizmo
{
    static GizmoState cfg = {};

    static bool32 isGizmoInited = false;
    static real32 axisWidth = 4;

    static void initGizmo(GizmoState &cfg)
    {
        cfg.mode = GizmoState::Mode::TRANSLATE;
    }

    static void drawTranslation(const glm::vec3 &pos)
    {
        glm::vec3 start = glm::vec3(0.0f, 0.0f, 0.0f);
        
        xe_graphics::Framebuffer *active_render_target = xe_render::getActiveFramebuffer();
        
        assert(active_render_target);
        
        xe_graphics::GraphicsDevice *graphics_device = xe_render::getDevice();

        xe_render::setupCommand(xe_render::CommandType::LINE);
        
        xe_render::drawLine(start.x, start.y, start.z, xe_math::VEC3_RIGHT.x, xe_math::VEC3_RIGHT.y, xe_math::VEC3_RIGHT.z);
        xe_render::drawLine(start.x, start.y, start.z, xe_math::VEC3_UP.x, xe_math::VEC3_UP.y, xe_math::VEC3_UP.z);
        xe_render::drawLine(start.x, start.y, start.z, xe_math::VEC3_BACK.x, xe_math::VEC3_BACK.y, xe_math::VEC3_BACK.z);
        
        xe_render::executeCommand(xe_render::CommandType::LINE);
    }

    static void updateAndDrawGizmo(const glm::vec3 &position, const glm::mat4 &view, const glm::mat4 &projection, GizmoState::Mode mode, GizmoState::Axis axe, GizmoState::CoordSystem cs)
    {
        xe_utility::info("Gizmo activated!!!");

        switch (mode)
        {
        case xe_gizmo::GizmoState::TRANSLATE:
            drawTranslation(position);
            break;
        case xe_gizmo::GizmoState::ROTATE:
            break;
        case xe_gizmo::GizmoState::SCALE:
            break;
        default:
            break;
        }


    }

    void manipulateGizmo(const glm::vec3 &position, const glm::mat4 &view, const glm::mat4 &projection, GizmoState::Mode mode, GizmoState::Axis axe, GizmoState::CoordSystem cs)
    {
        if (!isGizmoInited)
        {
            initGizmo(cfg);
            isGizmoInited = true;
        }

        updateAndDrawGizmo(position, view, projection, cfg.mode, axe, cs);
    }
}
