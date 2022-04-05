#pragma once
#include "cgCube.h"
#include "cgProgram.h"
class cgLightCube :
    public cgCube
{
public:
    cgLightCube();
    ~cgLightCube();

    void Render();
    void CalculateModelMatrix();
    void SetTextureID(unsigned int id);
    void SetScaleRatio(vec3 ratio);
    unsigned int GetTextureID();

protected:
    unsigned int textureID;
    vec3 scaleRatio;

};

