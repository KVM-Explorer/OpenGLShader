#include "pch.h"
#include "ColorPatch.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/constants.hpp>

using Range =  ColorPatch::Range;

/**
 * @brief ��ʼ��ɫ��
 * @param num ɫ����Ŀ
 * @detail  ��Ҫ��ǰ����Range
*/
ColorPatch::ColorPatch()
{

}
ColorPatch::~ColorPatch()
{
}
void ColorPatch::init(int num)
{
	blockNum = num;

	//todo


}

//void ColorPatch::calculateModelMatrix()
//{
//	//Todo 
//}

void ColorPatch::setPosition(vec3 position)
{
	modelMat = glm::translate(position);
}

void ColorPatch::setViewMatrix(mat4 view_mat)
{
	viewMat = view_mat;
}

void ColorPatch::setProjection(glm::mat4 project)
{
	projectionMat = project;
}

/**
 * @brief ��Ⱦɫ��
 * @detail ע��ʹ��ǰ����MVP
*/
void ColorPatch::render()
{
}

void ColorPatch::setRange(int min_value, int max_value, vec3 min_color, vec3 max_color)
{
	range = Range(min_value, max_value, min_color, max_color);
}

void ColorPatch::setColorMin(vec3 color)
{
	range.maxColor = color;
}

void ColorPatch::setColorMax(vec3 color)
{
	range.maxColor = color;
}

Range ColorPatch::getRange() const
{
	return range;
}
