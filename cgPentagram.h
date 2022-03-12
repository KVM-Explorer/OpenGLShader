#pragma once
#include "cgElement.h"
#include "pch.h"

class cgPentagram : public cgElement
{
public:
    explicit cgPentagram(float angle, vec3 trans);
    ~cgPentagram();

    void Init();
    void Render(mat4 projection);
    void SetType(int type);
    void CalculateModelMatrix();
    void GenerateVertex(float* vertex);
    void GenerateColor(float* vertex);
    
    int GetPosition();
    void SetPosition(int angle,vec3 position);
private:
    float alpha;
    vec3 translateVector;
    int pointNum;
    int colorType;
};