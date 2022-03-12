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
    unsigned int GetTextureID();

protected:
    unsigned int textureID;

};

