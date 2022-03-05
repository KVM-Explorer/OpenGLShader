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
    void CalculateModelMatrix();
    void GenerateVertex(float* vertex);
    void GenerateColor(float* vertex, int type);
private:
    float alpha;
    vec3 translateVector;
    const int pointNum = 10;
};