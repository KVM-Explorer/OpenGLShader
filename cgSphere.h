#pragma once
#include "cgElement.h"
class cgSphere :
    public cgElement
{
public:
    cgSphere();
    cgSphere(float r);
    ~cgSphere();

    void Init();
    void Render();
    void Render(mat4 projection);
    void SetPosition(vec3 position);
    vec3 GetPosition();
    void CalculateModelMatrix();
    void Update();
    void SetTextureID(unsigned int id);

private:
    vec3 centerPosition;
    int elementNum;
    float radius;
    unsigned int textureID;
};

