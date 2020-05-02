#pragma once

namespace xe_gui
{
    void init_imgui_impl();

    void start_frame();
    void end_frame();

    void draw_top_bar();

    void draw_button(const char *wo);

    void clear_context();
}
