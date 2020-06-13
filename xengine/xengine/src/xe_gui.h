#pragma once

namespace xe_gui
{
    void initImguiImpl();

    void startFrame();
    void endFrame();

    void drawTopBar();

    void drawButton(const char *wo);

    void clearContext();
}
