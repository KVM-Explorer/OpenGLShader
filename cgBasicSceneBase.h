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
};

