#pragma once
#include "cgElement.h"
#include <glm/glm.hpp>
#include "cgProgram.h"


#define PI 3.1415926

class cgElement
{
public:
	virtual void Render(mat4 projection) = 0;
	void Render();
	mat4 GetModelMatrix();
	
protected:
	cgProgram prog;
	mat4 model;
	unsigned int vboHandle[2];
	unsigned int vaoHandle;
};

