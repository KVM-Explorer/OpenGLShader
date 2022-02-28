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
private:
	float alpha;

};

