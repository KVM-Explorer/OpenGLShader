#include "pch.h"
#include "ToolBase.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtx/vector_angle.hpp>
using vec2 = glm::vec2;

mat4 ToolBase::CalculateModelMaxtrix(vec3 view_pos, vec3 view_head)
{
	mat4 model_mat;
	vec3 pos,rotate_vector;
	float ratio = 10;
	pos.x = view_pos.x + view_head.x * ratio;
	pos.y = view_pos.y + view_head.y * ratio;
	pos.z = view_pos.z + view_head.z * ratio;
	model_mat = glm::translate(pos);

	model_mat = model_mat * glm::translate(offset);
	rotate_vector = glm::cross(view_head, vec3(0.f, 1.f, 0.f));
	auto angle1 = glm::pi<float>() / 2.f - glm::angle(view_head, vec3(0.f, 1.f, 0.f));
	model_mat = model_mat * glm::rotate(angle1, rotate_vector);



	auto angle2 = abs(glm::angle(glm::normalize(vec2(view_head.x,view_head.z)),glm::normalize(vec2(0.f,-1.f))));	//x z ÈÆYÖáÐý×ª
	if (view_head.x > 0)angle2 = - angle2;
	//if (view_head.x < 0) angle = -angle;
	model_mat = model_mat * glm::rotate(angle2, vec3(0.f, 1.f, 0.f));
	
	//TRACE("X: %.2f Z: %.2f Y: %.2f Angle1:%.2f Angle2:%.2f\n", view_head.x,view_head.z,view_head.y, angle1/3.14*180.f,angle2/3.14f*180.f);


	return model_mat;
}

ToolBase::ToolBase():offset(vec3(400.f,-400.f,0.f))
{

}

void ToolBase::setOffset(vec3 offset)
{
	this->offset = offset;
}

ToolBase::~ToolBase()
{
}
