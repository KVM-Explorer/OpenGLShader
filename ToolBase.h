#pragma once
#include <gl/glew.h>
#include <glm/glm.hpp>
#include "Unit.h"
using vec3 = glm::vec3;
using mat4 = glm::mat4;

class ToolBase
{

protected:
	vec3 offset;


public:
	ToolBase();
	~ToolBase();
	mat4 CalculateModelMaxtrix(vec3 view_pos, vec3 view_head);
	void setOffset(vec3 offset);

};

