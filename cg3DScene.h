#pragma once
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/constants.hpp>
#include "cgSceneBase.h"
#include "cgTexture.h"

class cg3DScene :
    public cgSceneBase
{
public:
    cg3DScene();
    ~cg3DScene();

    void Init();
    void Render();
    void SetProjection(int width,int height);
    void Input(const unsigned int& key);
    void Update();
    void SetScene(int type);

protected:

    vec3 viewPos;
    vec3 viewHead;

    float yaw;
    float pitch;
    
    float alpha;
    float beta;
    int drawMode;
    int sceneType;

    cgProgram prog;
  
    cgTexture texture;
    cgProgram textureProg;
};

