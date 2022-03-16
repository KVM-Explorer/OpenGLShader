#pragma once


#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/constants.hpp>

#include "cgTexture.h"
#include "cgSceneBase.h"
#include "model.h"
#include "glslprogram.h"

class cgModelScene :
    public cgSceneBase
{
public:
    cgModelScene();
    ~cgModelScene();

    void Init();
    void Render();
    void SetProjection(int width, int height);
    void Input(const unsigned int& key);
    void Update();

    vec3 viewPos;
    vec3 viewHead;

    float alpha;
    float beta;

    int drawMode;

    cgProgram prog;
    cgProgram textureProg;
    GLSLProgram ourShader;

    cgTexture texture;
    cgTexture earthTexture;
    Model ourModel;

};

