#pragma once

#include "xe_graphics_resource.h"
#include "xe_ecs.h"
#include "perspective_camera.h"
#include "ortho_camera.h"

namespace xe_graphics
{
    class render_pass
    {
    public:

        virtual ~render_pass() {}

        virtual void init() = 0;
        virtual void clear() = 0;

        virtual void load_resources() = 0;
        virtual void unload_resources() = 0;

        virtual void render() = 0;

        virtual void update(float dt) = 0;

    private:
        
    };

    class render_pass2D : public render_pass
    {
    public:
        void init() override;
        void clear() override;

        void load_resources() override;
        void unload_resources() override;

        void render() override;

        void update(float dt) override;

        const texture2D& get_result_texture() { return result_texture; };

        inline XEngine::OrthoCamera& get_camera2d() { return camera2D; };
    private:
        XEngine::OrthoCamera camera2D;
        texture2D result_texture;
        shader* simple_shader;
        xe_ecs::entity main_ent;      
    };

    class render_pass3D : public render_pass
    {
    public:

        void init() override;
        void clear() override;

        void load_resources() override;
        void unload_resources() override;

        void render() override;

        void update(float dt) override;

        inline XEngine::PerspectiveCamera& get_camera3d() { return camera3D; }
    private:            
        XEngine::PerspectiveCamera camera3D;
        shader *model_shader;
        xe_ecs::entity ent;
        xe_assets::model *model;
        xe_assets::model *model_tree;
    };

    class gamma_correction_pass : public render_pass
    {
    public:
        void init() override;
        void clear() override;

        void load_resources() override;
        void unload_resources() override;

        void render() override;

        void update(float dt) override;
    private:
        shader* gmshd;
    };
}
