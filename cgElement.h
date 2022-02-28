#pragma once
#include "cgElement.h"
#include <glm/glm.hpp>
#include "cgProgram.h"
class cgElement
{
public:
	virtual void Render(mat4 projection) = 0;
	
protected:
	cgProgram prog;
	mat4 model;
	unsigned int vboHandle[2];
	unsigned int vaoHandle;
};

