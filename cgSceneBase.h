#pragma once
#include"cgElement.h"
#include<vector>
#include<memory>
class cgSceneBase
{
public:
	cgSceneBase();
	~cgSceneBase();

	void SetProjection(mat4 projection);
	void AddElement(std::shared_ptr<cgElement> pElement);

	virtual void Render() = 0;
	virtual void Init() = 0;
protected:
	std::vector <std::shared_ptr<cgElement>> elementsArray;
	mat4 mat4Projection;

};

