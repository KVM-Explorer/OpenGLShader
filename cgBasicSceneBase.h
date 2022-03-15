#pragma once
#include "cgSceneBase.h"
class cgBasicSceneBase :public cgSceneBase
{
public:
	cgBasicSceneBase();
	~cgBasicSceneBase();

	void Init();
	void Render();
	void Update();
	void SetProjection(mat4 projection);
	void SetProjection(int width, int height);
	void AddElement(std::shared_ptr<cgElement> element);
	


};

