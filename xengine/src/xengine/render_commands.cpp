#include "render_commands.h"

RenderCommandStaticModel::RenderCommandStaticModel(Transform *transf, Model *mod, Material *mat) : transform_data(transf), static_model_ptr(mod), mat_ptr(mat)
{

}

RenderCommandStaticModel::~RenderCommandStaticModel()
{
    transform_data = 0;
    static_model_ptr = 0;
    mat_ptr = 0;
}

void RenderCommandStaticModel::execute()
{
    Render::pushCommand([&]()
    {
        Camera3D &camera3d = getCamera3D();
        Matrix4x4 modelMat = translateMat(transform_data->pos) * scaleMat(transform_data->scale);

        Matrix4x4 vp = camera3d.getViewProjectionMatrix();
        Matrix4x4 mvp = vp * modelMat;

        Matrix4x4 inverseMMatrix = inverseMat(modelMat);
        transposeMat4x4(inverseMMatrix);
        Matrix3x3 normal_matrix = convertFrom(inverseMMatrix);

        mat_ptr->set("mvp", ShaderUniformType::Mat4x4, &mvp);
        mat_ptr->set("vp", ShaderUniformType::Mat4x4, &vp);
        mat_ptr->set("model", ShaderUniformType::Mat4x4, &modelMat);
        mat_ptr->set("normalMatrix", ShaderUniformType::Mat3x3, &normal_matrix);

        Render::drawModel(static_model_ptr, mat_ptr);
    });
}

PostProcPassCommand::PostProcPassCommand(Material *mat, RenderPass *pass) : mat_ptr(mat), pass_ptr(pass)
{
    static bool32 isAdded = false;
    if (!isAdded)
    {
        Texture2D *albedo = pass_ptr->getTexture2D(2);
        Texture2D *normal = pass_ptr->getTexture2D(1);
        Texture2D *depth  = pass_ptr->getTexture2D(4);

        mat_ptr->addTexture2D(albedo);
        mat_ptr->addTexture2D(normal);
        mat_ptr->addTexture2D(depth);

        isAdded = true;
    }
}

PostProcPassCommand::~PostProcPassCommand()
{
    pass_ptr = 0;
    mat_ptr = 0;
}

global Vec3 light_pos = createVec3(0.0f, 0.0f, 4.0f);

void PostProcPassCommand::execute()
{
    Render::pushCommand([&]()
    {
        Camera3D &camera3d = getCamera3D();

        mat_ptr->set("viewPos", ShaderUniformType::Vec3Uniform, &camera3d.pos);
        mat_ptr->set("lightPos", ShaderUniformType::Vec3Uniform, &light_pos);

        mat_ptr->set("viewInverse", ShaderUniformType::Mat4x4, &camera3d.getViewInverseMatrix());
        mat_ptr->set("projectionInverse", ShaderUniformType::Mat4x4, &camera3d.getProjectionInverseMatrix());

        Render::drawFullquad(mat_ptr);
    });
}
