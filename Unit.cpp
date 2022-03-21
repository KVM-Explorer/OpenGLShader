#include "pch.h"
#include "Unit.h"
#include <GL/glew.h>



void Unit::setDrawMode(Mode mode)
{
	drawMode = mode;
}

// 初始化8个顶点，目前假定颜色求解可以放在shader进行
void Unit::init(std::shared_ptr<float[]> data)
{
	// 根据顶点坐标生成矩阵

	auto v = std::shared_ptr<float[]>(new float[elementNum * 3]);
	auto c = std::shared_ptr<float[]>(new float[elementNum * 3]);
	int vindex = 0;
	int cindex = 0;
	genElement(v, data, vindex, 0, 1, 2, 3);
	genElement(v, data, vindex, 1, 2, 6, 5);
	genElement(v, data, vindex, 0, 3, 7, 4);
	genElement(v, data, vindex, 0, 1, 5, 4);
	genElement(v, data, vindex, 4, 5, 6, 7);
	genElement(v, data, vindex, 2, 3, 7, 6);

	genElement(c, data, cindex, 0, 1, 2, 3);
	genElement(c, data, cindex, 1, 2, 6, 5);
	genElement(c, data, cindex, 0, 3, 7, 4);
	genElement(c, data, cindex, 0, 1, 5, 4);
	genElement(c, data, cindex, 4, 5, 6, 7);
	genElement(c, data, cindex, 2, 3, 7, 6);

	// buffer
	glGenBuffers(2, vboHandle);
	glGenVertexArrays(1, &vaoHandle);
	glBindVertexArray(vaoHandle);

	glBindBuffer(GL_ARRAY_BUFFER, vboHandle[0]);
	glBufferData(GL_ARRAY_BUFFER, 3 * 3 * elementNum * sizeof(float), v.get(), GL_STATIC_DRAW);
	glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, ((GLubyte*)NULL + (0)));
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, vboHandle[1]);
	glBufferData(GL_ARRAY_BUFFER, 3 * 3 * elementNum * sizeof(float), v.get(), GL_STATIC_DRAW);
	glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, ((GLubyte*)NULL + (0)));
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
}

void Unit::genElement(std::shared_ptr<float[]> dst, std::shared_ptr<float[]> src, int& vindex, int a, int b, int c, int d)
{
	// triangle 1
	dst[vindex++] = src[3 * a], dst[vindex++] = src[3 * a + 1], dst[vindex++] = src[3 * a + 2];
	dst[vindex++] = src[3 * b], dst[vindex++] = src[3 * b + 1], dst[vindex++] = src[3 * b + 2];
	dst[vindex++] = src[3 * c], dst[vindex++] = src[3 * c + 1], dst[vindex++] = src[3 * c + 2];

	// triangle 2
	dst[vindex++] = src[3 * c], dst[vindex++] = src[3 * c + 1], dst[vindex++] = src[3 * c + 2];
	dst[vindex++] = src[3 * d], dst[vindex++] = src[3 * d + 1], dst[vindex++] = src[3 * d + 2];
	dst[vindex++] = src[3 * a], dst[vindex++] = src[3 * a + 1], dst[vindex++] = src[3 * a + 2];
}

void Unit::genColor(std::shared_ptr<float[]> dst, std::shared_ptr<float[]> src, int& cindex, int a, int b, int c, int d)
{
	// triangle 1
	dst[cindex++] = 0.5, dst[cindex++] = 0.5, dst[cindex++] = 0.5;
	dst[cindex++] = 0.5, dst[cindex++] = 0.5, dst[cindex++] = 0.5;
	dst[cindex++] = 0.5, dst[cindex++] = 0.5, dst[cindex++] = 0.5;

	// triangle 2
	dst[cindex++] = 0.5, dst[cindex++] = 0.5, dst[cindex++] = 0.5;
	dst[cindex++] = 0.5, dst[cindex++] = 0.5, dst[cindex++] = 0.5;
	dst[cindex++] = 0.5, dst[cindex++] = 0.5, dst[cindex++] = 0.5;
}

void Unit::render()
{
	glBindVertexArray(vaoHandle);
	glDrawArrays(GL_TRIANGLES, 0, 3 * elementNum);
	glBindVertexArray(0);
}
