#pragma once
#include "cgElement.h"
class cgCylinder :
    public cgElement
{
public: 
    cgCylinder();
    cgCylinder(float r, float h);
    ~cgCylinder();

    void Init();
    void Render();
    void Render(mat4 projection);
    void SetPosition(vec3 position);
    vec3 GetPosition();
    void CalcuteModelMatrix();
    void Update();

    void SetTextureID(unsigned int texture_id);
    unsigned int GetTextureID();

private:
    vec3 centerPosition;
    int elementNum;
    float radius;
    float height;

    unsigned int textureID;
};
