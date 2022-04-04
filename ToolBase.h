#pragma once
#include <gl/glew.h>
#include <glm/glm.hpp>
using vec3 = glm::vec3;
using mat4 = glm::mat4;

class ToolBase
{

protected:
	vec3 offset;


public:
	mat4 CalculateModelMaxtrix(vec3 view_pos, vec3 view_head);
	

};

