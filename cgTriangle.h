#pragma once
#include "cgElement.h"
class cgTriangle :public cgElement
{
public:
	cgTriangle();
	~cgTriangle();

	void Init();
	void Render(mat4 projection);
	void CalculateModelMatrix();
	void Render();
	void SetPosition(vec3 position);
	vec3 GetPosition();
	
private:
	float alpha;
	int elementNum;
	vec3 centerPosition;
};

