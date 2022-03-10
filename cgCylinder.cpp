#include "pch.h"
#include "cgCylinder.h"
#include <math.h>
#include <GL/glew.h>//OpenGL库
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/constants.hpp>

cgCylinder::cgCylinder()
{
	radius = 5;
	height = 10;
	elementNum = 0;
	centerPosition = vec3(0, 0, 0);
}

cgCylinder::cgCylinder(float r, float h)
{
	radius = r;
	height = h;
	elementNum = 0;
	centerPosition = vec3(0, 0, 0);
}

cgCylinder::~cgCylinder()
{
}

void cgCylinder::Init()
{
	int m = 20;	// 圆分片
	int n = 20;	// 高分片
	elementNum = m * n * 2 + 2 * m;

	float* vertex = new float[3 * 3 * elementNum];
	float* normal = new float[3 * 3 * elementNum];

	float dalpha = 2 * PI / m;
	float dh = (float)height / (float)n;
	float h = -height / 2;

	int vindex = 0;
	int nindex = 0;
	vec3 vnormal;

	// 侧面
	for (int i = 0; i < n; i++)
	{
		float alpha = 0.f;	// 圆周
		float z1 = h;
		float z2 = h + dh;

		h += dh;
		for (int j = 0; j < m; j++)
		{
			float x01 = radius * cos(alpha);
			float y01 = radius * sin(alpha);

			float x02 = radius * cos(alpha + dalpha);
			float y02 = radius * sin(alpha + dalpha);

			float x11 = radius * cos(alpha);
			float y11 = radius * sin(alpha);

			float x12 = radius * cos(alpha + dalpha);
			float y12 = radius * sin(alpha + dalpha);
			// 第一个三角形
			vertex[vindex++] = x01; vertex[vindex++] = y01; vertex[vindex++] = z1;
			vnormal = glm::normalize(vec3(x01, y01, z1));
			normal[nindex++] = vnormal.x; normal[nindex++] = vnormal.y; normal[nindex++] = vnormal.z;

			vertex[vindex++] = x02; vertex[vindex++] = y02; vertex[vindex++] = z1;
			vnormal = glm::normalize(vec3(x02, y02, z1));
			normal[nindex++] = vnormal.x; normal[nindex++] = vnormal.y; normal[nindex++] = vnormal.z;

			vertex[vindex++] = x11; vertex[vindex++] = y11; vertex[vindex++] = z2;
			vnormal = glm::normalize(vec3(x11, y11, z2));
			normal[nindex++] = vnormal.x; normal[nindex++] = vnormal.y; normal[nindex++] = vnormal.z;

			// 第二个三角形
			vertex[vindex++] = x02; vertex[vindex++] = y02; vertex[vindex++] = z1;
			vnormal = glm::normalize(vec3(x02, y02, z1));
			normal[nindex++] = vnormal.x; normal[nindex++] = vnormal.y; normal[nindex++] = vnormal.z;

			vertex[vindex++] = x12; vertex[vindex++] = y12; vertex[vindex++] = z2;
			vnormal = glm::normalize(vec3(x12, y12, z2));
			normal[nindex++] = vnormal.x; normal[nindex++] = vnormal.y; normal[nindex++] = vnormal.z;

			vertex[vindex++] = x11; vertex[vindex++] = y11; vertex[vindex++] = z2;
			vnormal = glm::normalize(vec3(x11, y11, z2));
			normal[nindex++] = vnormal.x; normal[nindex++] = vnormal.y; normal[nindex++] = vnormal.z;



			alpha += dalpha;
		}
	}
	
	// 上顶面
	float alpha = 0.f;
	for (int i = 0; i < m; i++)
	{
		
		float z1 = height / 2;
		
		float x01 = radius * cos(alpha);
		float y01 = radius * sin(alpha);

		float x02 = radius * cos(alpha + dalpha);
		float y02 = radius * sin(alpha + dalpha);

		float x11 = 0;
		float y11 = 0;

		// 第一个三角形
		vertex[vindex++] = x01; vertex[vindex++] = y01; vertex[vindex++] = z1;
		vnormal = glm::normalize(vec3(x01, y01, z1));
		normal[nindex++] = vnormal.x; normal[nindex++] = vnormal.y; normal[nindex++] = vnormal.z;

		vertex[vindex++] = x02; vertex[vindex++] = y02; vertex[vindex++] = z1;
		vnormal = glm::normalize(vec3(x02, y02, z1));
		normal[nindex++] = vnormal.x; normal[nindex++] = vnormal.y; normal[nindex++] = vnormal.z;

		vertex[vindex++] = x11; vertex[vindex++] = y11; vertex[vindex++] = z1;
		vnormal = glm::normalize(vec3(x11, y11, z1));
		normal[nindex++] = vnormal.x; normal[nindex++] = vnormal.y; normal[nindex++] = vnormal.z;


		alpha += dalpha;
	}

	// 下顶面
	alpha = 0.f;
	for (int i = 0; i < m; i++)
	{
		float z1 = -height / 2;

		float x01 = radius * cos(alpha);
		float y01 = radius * sin(alpha);

		float x02 = radius * cos(alpha + dalpha);
		float y02 = radius * sin(alpha + dalpha);

		float x11 = 0;
		float y11 = 0;

		// 第一个三角形
		vertex[vindex++] = x01; vertex[vindex++] = y01; vertex[vindex++] = z1;
		vnormal = glm::normalize(vec3(x01, y01, z1));
		normal[nindex++] = vnormal.x; normal[nindex++] = vnormal.y; normal[nindex++] = vnormal.z;

		vertex[vindex++] = x02; vertex[vindex++] = y02; vertex[vindex++] = z1;
		vnormal = glm::normalize(vec3(x02, y02, z1));
		normal[nindex++] = vnormal.x; normal[nindex++] = vnormal.y; normal[nindex++] = vnormal.z;

		vertex[vindex++] = x11; vertex[vindex++] = y11; vertex[vindex++] = z1;
		vnormal = glm::normalize(vec3(x11, y11, z1));
		normal[nindex++] = vnormal.x; normal[nindex++] = vnormal.y; normal[nindex++] = vnormal.z;


		alpha += dalpha;
	}

	glGenBuffers(3, vboHandle);//生成缓冲区，数据

	glGenVertexArrays(1, &vaoHandle);//生成顶点数组，与vertex shader绑定
	glBindVertexArray(vaoHandle);//可以多个顶点数组，使用时需要激活哪一个

	glBindBuffer(GL_ARRAY_BUFFER, vboHandle[0]);//激活（绑定）当前缓冲区
	glBufferData(GL_ARRAY_BUFFER, 3 * 3 * elementNum * sizeof(float), vertex, GL_STATIC_DRAW);//内存数据复制到显存
	glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, ((GLubyte*)NULL + (0)));//Vertex Shader的顶点坐标输入属性（序号0，坐标）对应
	glEnableVertexAttribArray(0);  // 允许Vertex着色器中输入变量0读取显存数据。

	glBindBuffer(GL_ARRAY_BUFFER, vboHandle[1]);//缓冲区数据（颜色）和顶点绑定
	glBufferData(GL_ARRAY_BUFFER, 3 * 3 * elementNum * sizeof(float), normal, GL_STATIC_DRAW);//内存数据复制到显存
	glVertexAttribPointer((GLuint)1, 3, GL_FLOAT, GL_FALSE, 0, ((GLubyte*)NULL + (0)));//Vertex Shader的顶点颜色输入（序号1，颜色）属性对应
	glEnableVertexAttribArray(1);  //  // 允许Vertex着色器中输入变量1读取显存数据。

	//glBindBuffer(GL_ARRAY_BUFFER, vboHandle[2]);//缓冲区数据（颜色）和顶点绑定
	//glBufferData(GL_ARRAY_BUFFER, 3 * 2 * iCount * sizeof(float), textcor, GL_STATIC_DRAW);//内存数据复制到显存
	//glVertexAttribPointer((GLuint)2, 2, GL_FLOAT, GL_FALSE, 0, ((GLubyte*)NULL + (0)));//Vertex Shader的顶点颜色输入（序号1，颜色）属性对应
	//glEnableVertexAttribArray(1);  //  // 允许Vertex着色器中输入变量1读取显存数据。

	glBindVertexArray(0);

	delete[] vertex;
	delete[] normal;
}

void cgCylinder::Render()
{
	glBindVertexArray(vaoHandle);
	glDrawArrays(GL_TRIANGLES, 0, 3 * elementNum);
	glBindVertexArray(0);
}

void cgCylinder::Render(mat4 projection)
{
	// Empty
}

void cgCylinder::SetPosition(vec3 position)
{
	centerPosition = position;
}

vec3 cgCylinder::GetPosition()
{
	return centerPosition;
}

void cgCylinder::CalcuteModelMatrix()
{
	model = glm::translate(centerPosition);
}

void cgCylinder::Update()
{
	//Empty
}
