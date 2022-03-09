#pragma once
#include "cgElement.h"
class cgCube :
    public cgElement
{
public:
    cgCube();
    ~cgCube();

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
    void polygon(float *vertex, int &index, int a,int b,int c,int d, float data[8][3]);


};

