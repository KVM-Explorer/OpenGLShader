#pragma once
#include "cgElement.h"
#include <tuple>
#include <vector>
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
    void SetRotateInfo(std::vector<float> angle, std::vector<vec3> roller);
    vec3 GetPosition();
    void CalcuteModelMatrix();
    void Update();

    void SetTextureID(unsigned int texture_id);
    unsigned int GetTextureID();

protected:
    vec3 centerPosition;
    std::tuple<std::vector<float>, std::vector<vec3>> rotateInfo;
    int elementNum;
    float radius;
    float height;

    unsigned int textureID;
};

