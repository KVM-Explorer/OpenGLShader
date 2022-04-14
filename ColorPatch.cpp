#include "pch.h"
#include "ColorPatch.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/constants.hpp>
#include <memory>
#include <gl/glew.h>
#include <glm/gtx/color_space.hpp>

using Range = ColorPatch::Range;

/**
 * @brief 初始化色标
 * @param num 色标数目
 * @detail  需要提前设置Range
*/
ColorPatch::ColorPatch()
{
	colorType = ColorType::hsv;
	blockNum = 10;
}
ColorPatch::~ColorPatch()
{
}
/**
 * @brief 生成色标方格
 * @details 使用前调用OpenGL上下文
*/
void ColorPatch::init()
{
	auto v = std::shared_ptr<float[]>(new float[blockNum * 2 * 3*3]);
	auto c = std::shared_ptr<float[]>(new float[blockNum * 2 * 3 ]);
	int vindex = 0;
	int cindex = 0;

	genBlocks(v, vindex);
	//genSingleColor(c, cindex);
	
	glGenBuffers(2, vboHandle);
	glGenVertexArrays(1, &vaoHandle);

	glBindVertexArray(vaoHandle);
	glBindBuffer(GL_ARRAY_BUFFER, vboHandle[0]);
	glBufferData(GL_ARRAY_BUFFER, 3 * 3 * 2 * blockNum * sizeof(float),v.get(),GL_STATIC_DRAW);
	glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, ((GLubyte*)NULL+(0)));
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, vboHandle[1]);
	glBufferData(GL_ARRAY_BUFFER, 2 * 3 * blockNum * sizeof(float), NULL, GL_STATIC_DRAW);
	glVertexAttribPointer((GLuint)1, 1, GL_FLOAT, GL_FALSE, 0, ((GLbyte*)NULL + (0)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);


}


void ColorPatch::setBlockNum(int num)
{
	blockNum = num;
}

int ColorPatch::getBlockNum() const
{
	return blockNum;
}






/**
 * @brief 渲染色标
 * @detail 注意使用前设置MVP
*/
void ColorPatch::render()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBindVertexArray(vaoHandle);
	glDrawArrays(GL_TRIANGLES, 0, 3 * 2 * blockNum);
	glBindVertexArray(0);
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

void ColorPatch::setColorType(ColorType type)
{
	colorType = type;
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
	if (colorType == ColorType::hsv) return vec3(range.minColor.r / 360.f, range.minColor.g, range.minColor.b);
	if (colorType == ColorType::rgb) return rgbColor(range.minColor);
}

vec3 ColorPatch::getMaxColor() const
{
	if (colorType == ColorType::hsv) return vec3(range.maxColor.x / 360.f, range.maxColor.y, range.maxColor.z);
	if (colorType == ColorType::rgb) return rgbColor(range.maxColor);
}

ColorPatch::ColorType ColorPatch::getColorType() const
{	
	return colorType;
}

void ColorPatch::updateBlockValue(RenderMode mode)
{
	glBindBuffer(GL_ARRAY_BUFFER, vboHandle[1]);

	auto color = std::shared_ptr<float[]>(new float[blockNum * 2 * 3]);
	int cindex = 0;
	switch (mode)
	{
	case RenderMode::single:
		genSingleColor(color, cindex);
		break;
	case RenderMode::smooth:
		genSmoothColor(color, cindex);
		break;
	default:
		break;
	}
	glBufferData(GL_ARRAY_BUFFER, blockNum * 2 * 3 * sizeof(float), color.get(), GL_STATIC_DRAW);

}

/**
 * @brief 生成块
 * @param dst 
 * @details 假定blocks是偶数
*/
void ColorPatch::genBlocks(std::shared_ptr<float[]> dst,int &vindex)
{
	float width = 20.f;
	float height = 20.f;
	float st = -height * blockNum/2;
	for (int i = 0; i < blockNum; i++)
	{
		// 三角形1
		dst[vindex + 0] = -width / 2.f, dst[vindex + 1] = st, dst[vindex + 2] = 0;
		dst[vindex + 3] = width / 2.f, dst[vindex + 4] = st, dst[vindex + 5] = 0;
		dst[vindex + 6] = width / 2.f, dst[vindex + 7] = st + height, dst[vindex + 8] = 0;
		vindex += 9;

		// 三角形2
		dst[vindex + 0] = width / 2.f, dst[vindex + 1] = st+height, dst[vindex + 2] = 0;
		dst[vindex + 3] = -width / 2.f, dst[vindex + 4] = st+height, dst[vindex + 5] = 0;
		dst[vindex + 6] = -width / 2.f, dst[vindex + 7] = st, dst[vindex + 8] = 0;
		vindex += 9;

		st = st + height;
	}
}

void ColorPatch::genSingleColor(std::shared_ptr<float[]> dst, int& cindex)
{
	float st = range.minValue;
	float step = (range.maxValue-range.minValue) / blockNum;

	for (int i = 0; i < blockNum; i++)
	{

		dst[cindex++] = st, dst[cindex++] = st, dst[cindex++] = st;
		dst[cindex++] = st, dst[cindex++] = st, dst[cindex++] = st;
		
		st += step;
	}
}

void ColorPatch::genSmoothColor(std::shared_ptr<float[]> dst, int& cindex)
{
	float st = range.minValue;
	float step = (range.maxValue - range.minValue) / blockNum;

	for (int i = 0; i < blockNum; i++)
	{
		
		dst[cindex++] = st; dst[cindex++] = st; dst[cindex++] = st+step;
		dst[cindex++] = st + step; dst[cindex++] = st + step; dst[cindex++] = st;
		st += step;
	}
}
