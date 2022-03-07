#pragma once
#include "cgElement.h"
#include "pch.h"

class cgRectangle :public cgElement
{
public:
	cgRectangle(float angle = 0, vec3 trans = vec3(0, 0, 0));
	~cgRectangle();
	void Init();
	void Render(mat4 projection);
	void CalculateModelMatrix();

	void GenerateVertex(float*);
	void GenerateColor(float*,int);
private:
	float alpha;
    vec3 translateVector;
    const int pointNum = 4;

};

