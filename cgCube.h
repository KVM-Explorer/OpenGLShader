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
    virtual void CalculateModelMatrix();
    void Update();
    
    void SetTextureID(unsigned int texture_id);
    unsigned int GetTextureID();

    
protected:
    vec3 centerPosition;
    int elementNum;
    void polygon(float *vertex, float* textcol, int &index, int& tindex,int a,int b, int c, int d, float data[8][3]);

    unsigned int textureID;
};

