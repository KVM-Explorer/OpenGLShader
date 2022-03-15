#pragma once
#include "cgSceneBase.h"
class cgCollisionBounce :public cgSceneBase
{
public:
	cgCollisionBounce();
	~cgCollisionBounce();

	void Init();
	void Render();
    void Update();
    void SetProjection(int width, int height);
    void SetProjection(mat4 projection);
private:
    int beta;
    int positionX;
    int positionY;
    int deltaX;
    int deltaY;
};

