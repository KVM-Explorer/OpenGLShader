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

private:
    vec3 centerPosition;
    int elementNum;
    float radius;
};

