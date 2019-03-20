#pragma once

#ifndef SKYBOXH
#define SKYBOXH

#include "../core/rendering/pipeline/shader.h"
#include "../core/rendering/texture.h"
#include "../core/cameras/camera.h"
#include "../core/rendering/openglnew/vao.h"

class __declspec(dllexport) Skybox
{
public:
    Skybox() 
    {
        sky = (GeometryBuffer*)malloc(sizeof(GeometryBuffer));
    };
    ~Skybox()
    {
        free(sky);
    }

    void createSkybox();
    void initShader();
    void renderSkybox(Shader * shader, XEngine::FlyCamera *cam, glm::mat4& v, glm::mat4& proj, uint32& tex);
    GeometryBuffer* getGeometryBuffer() { return sky; };
private:
    GeometryBuffer *sky;
};


#endif // !SKYBOX

