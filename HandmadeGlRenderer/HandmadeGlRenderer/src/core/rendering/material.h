#pragma once


#ifndef MATERIAL_H
#define MATERIAL_H

#include "../../application/xenpch.h"
#include "../../core/types.h"


struct __declspec(dllexport) Material 
{
    glm::vec4 diffuseColor;
    glm::vec4 specularColor ;
    glm::vec4 glowColor;

    uint32 diffuseMapTexture;
    uint32 normalMapTexture;
    uint32 specularMapTexture;
    uint32 bumpMapTexture;
    real32 shininess = 1.0f;
    real32 bumpMapStrength = 1.0f;

};
#endif