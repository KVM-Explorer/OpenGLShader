#include "pch.h"
#include "Unit.h"
#include <GL/glew.h>



void Unit::setDrawMode(Mode mode)
{
	drawMode = mode;
}

// 初始化8个顶点，目前假定颜色求解可以放在shader进行
void Unit::init(std::shared_ptr<float[]> data, int st)
{
	 //根据顶点坐标生成矩阵

	auto v = std::shared_ptr<float[]>(new float[elementNum * 3*3]);
	int vindex = 0;

	genElement(v, data,st , vindex, 0, 1, 2, 3);
	genElement(v, data,st , vindex, 1, 2, 6, 5);
	genElement(v, data, st, vindex, 0, 3, 7, 4);
	genElement(v, data, st, vindex, 0, 1, 5, 4);
	genElement(v, data, st, vindex, 4, 5, 6, 7);
	genElement(v, data, st, vindex, 2, 3, 7, 6);


	 //buffer
	glGenBuffers(4, vboHandle);
	glGenVertexArrays(1, &vaoHandle);

	glBindVertexArray(vaoHandle);

	glBindBuffer(GL_ARRAY_BUFFER, vboHandle[0]);
	glBufferData(GL_ARRAY_BUFFER, 3 * 3 * elementNum * sizeof(float), v.get(), GL_STATIC_DRAW);
	glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, ((GLubyte*)NULL + (0)));
	glEnableVertexAttribArray(0);	// shader layout = 0

	glBindVertexArray(0);
}

void Unit::setValue(float data)
{
	auto c = std::shared_ptr<float[]>(new float[elementNum * 3 ]);
	
	int cindex = 0;
	genSingleColor(c, data, cindex);
	glBindVertexArray(vaoHandle);

	glBindBuffer(GL_ARRAY_BUFFER, vboHandle[1]);
	glBufferData(GL_ARRAY_BUFFER, 3 * elementNum * sizeof(float), c.get(), GL_STATIC_DRAW);
	glVertexAttribPointer((GLuint)1, 1, GL_FLOAT, GL_FALSE, 0, ((GLubyte*)NULL + (0)));

	glEnableVertexAttribArray(1);

	glBindVertexArray(0);



	//glBindBuffer(GL_ARRAY_BUFFER,vboHandle[1]);
	//float* ptr = (float*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);


	//// if the pointer is valid(mapped), update VBO
	//if (ptr)
	//{
	//	std::memcpy(ptr,c.get(),sizeof(float)*elementNum*3);               // modify buffer data
	//	glUnmapBufferARB(GL_ARRAY_BUFFER_ARB); // unmap it after use
	//}
}

void Unit::setValue(std::vector<float> data)
{
	auto c = std::shared_ptr<float[]>(new float[elementNum * 3]);
	int cindex = 0;
	auto size = data.size();
	genSmooth(c, data, cindex, 0, 1, 3, 2);
	genSmooth(c, data, cindex, 1, 3, 7, 5);
	genSmooth(c, data, cindex, 0, 2, 6, 4);
	genSmooth(c, data, cindex, 0, 1, 5, 4);
	genSmooth(c, data, cindex, 4, 5, 7, 6);
	genSmooth(c, data, cindex, 3, 2, 6, 7);

	glBindVertexArray(vaoHandle);

	glBindBuffer(GL_ARRAY_BUFFER, vboHandle[1]);
	glBufferData(GL_ARRAY_BUFFER, 3 * elementNum * sizeof(float), c.get(), GL_STATIC_DRAW);
	glVertexAttribPointer((GLuint)1, 1, GL_FLOAT, GL_FALSE, 0, ((GLubyte*)NULL + (0)));
	glEnableVertexAttribArray(1);	// shader layout = 0

	glBindVertexArray(0);

}

void Unit::genElement(std::shared_ptr<float[]> dst, std::shared_ptr<float[]> src, int st, int& vindex, int a, int b, int c, int d)
{
	// triangle 1
	dst[vindex++] = src[st + 3 * a], dst[vindex++] = src[st + 3 * a + 1], dst[vindex++] = src[st + 3 * a + 2];
	dst[vindex++] = src[st + 3 * b], dst[vindex++] = src[st + 3 * b + 1], dst[vindex++] = src[st + 3 * b + 2];
	dst[vindex++] = src[st + 3 * c], dst[vindex++] = src[st + 3 * c + 1], dst[vindex++] = src[st + 3 * c + 2];

	// triangle 2
	dst[vindex++] = src[st + 3 * c], dst[vindex++] = src[st + 3 * c + 1], dst[vindex++] = src[st + 3 * c + 2];
	dst[vindex++] = src[st + 3 * d], dst[vindex++] = src[st + 3 * d + 1], dst[vindex++] = src[st + 3 * d + 2];
	dst[vindex++] = src[st + 3 * a], dst[vindex++] = src[st + 3 * a + 1], dst[vindex++] = src[st + 3 * a + 2];
}

void Unit::genSingleColor(std::shared_ptr<float[]> dst, float src, int& cindex)
{
	for (int i = 0; i < elementNum*3; i++)
	{
		dst[cindex++] = src;
	}
}
 

void Unit::genSmooth(std::shared_ptr<float[]> dst, std::vector<float> &src, int& cindex, int a, int b, int c, int d)
{
	dst[cindex++] = src[a], dst[cindex++] = src[b], dst[cindex++] = src[c];
	dst[cindex++] = src[c], dst[cindex++] = src[d], dst[cindex++] = src[a];
}

void Unit::genIsopleth(std::shared_ptr<float[]> dst, std::shared_ptr<float[]> src, int st, int& cindex, int a, int b, int c, int d)
{
	// Todo
}

void Unit::render()
{
	glBindVertexArray(vaoHandle);
	glDrawArrays(GL_TRIANGLES, 0, 3 * elementNum); 
	glBindVertexArray(0);
}
