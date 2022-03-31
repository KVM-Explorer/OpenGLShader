#include "pch.h"
#include "ColorPatch.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/constants.hpp>

using Range =  ColorPatch::Range;

/**
 * @brief 初始化色标
 * @param num 色标数目
 * @detail  需要提前设置Range
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
	// Todo
}


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
 * @brief 渲染色标
 * @detail 注意使用前设置MVP
*/
void ColorPatch::render()
{
}

void ColorPatch::setRange(float min_value, float max_value, vec3 min_color, vec3 max_color)
{
	range = Range(min_value, max_value, min_color, max_color);
}

void ColorPatch::setRange(float min_val, float max_val)
{
	range.minValue = min_val;
	range.maxValue = max_val;
}



void ColorPatch::setColorMin(vec3 color)
{
	range.minColor = color;

}


void ColorPatch::setColorMax(vec3 color)
{
	range.maxColor = color;
}

Range ColorPatch::getRange() const
{
	return range;
}

vec3 ColorPatch::getMinColor() const
{
	return range.minColor;
}

vec3 ColorPatch::getMaxColor() const
{
	return range.maxColor;
}
