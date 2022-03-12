#include "pch.h"
#include "cgCube.h"
#include <math.h>
#include <GL/glew.h>//OpenGL库
#include <vector>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/constants.hpp>

cgCube::cgCube()
{
	centerPosition = vec3(0.f, 0.f, -10.f);
	elementNum = 0;
}

cgCube::~cgCube()
{
}

void cgCube::Init()
{
	// Generate Points
	elementNum = 6 * 2;
	float origin[8][3] =
		{ 
			{-1,-1,-1},{1,-1,-1},{1,1,-1},{-1,1,-1},
			{-1,-1,1},{1,-1,1},{1,1,1},{-1,1,1}
		};
	int vindex = 0;
	int nindex = 0;
	int tindex = 0;

	float* vertex = new float[3 * 3 * elementNum];
	float* normal = new float[3 * 3 * elementNum];
	float* textcol = new float[3 * 2 * elementNum];

	// 顶面
	polygon(vertex,textcol ,vindex,tindex ,7,6, 2, 3, origin);
	for (int i = 0; i < 6; i++)
	{
		normal[nindex++] = 0; normal[nindex++] = 1; normal[nindex++] = 0;
	}

	// 底面
	polygon(vertex, textcol, vindex, tindex, 4, 5, 1, 0, origin);
	for (int i = 0; i < 6; i++)
	{
		normal[nindex++] = 0; normal[nindex++] = -1; normal[nindex++] = 0;
	}

	// 前面
	polygon(vertex, textcol, vindex, tindex,4,5, 6, 7, origin);
	for (int i = 0; i < 6; i++)
	{
		normal[nindex++] = 0; normal[nindex++] = 0; normal[nindex++] = 1;
	}

	// 后面
	polygon(vertex, textcol,vindex,tindex ,0,1, 2, 3, origin);
	for (int i = 0; i < 6; i++)
	{
		normal[nindex++] = 0; normal[nindex++] = 0; normal[nindex++] = -1;
	}

	// 左面
	polygon(vertex, textcol, vindex, tindex,0,3, 7, 4, origin);
	for (int i = 0; i < 6; i++)
	{
		normal[nindex++] = -1; normal[nindex++] = 0; normal[nindex++] = 0;
	}
	// 右面
	polygon(vertex, textcol, vindex, tindex,1,2, 6, 5, origin);
	for (int i = 0; i < 6; i++)
	{
		normal[nindex++] = 1; normal[nindex++] = 0; normal[nindex++] = 0;
	}

	glGenBuffers(2, vboHandle);//生成缓冲区，数据

	glGenVertexArrays(1, &vaoHandle);//生成顶点数组，与vertex shader绑定
	glBindVertexArray(vaoHandle);//可以多个顶点数组，使用时需要激活哪一个

	glBindBuffer(GL_ARRAY_BUFFER, vboHandle[0]);//激活（绑定）当前缓冲区
	glBufferData(GL_ARRAY_BUFFER, 3 * 3 * elementNum * sizeof(float), vertex, GL_STATIC_DRAW);//内存数据复制到显存
	glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, ((GLubyte*)NULL + (0)));//Vertex Shader的顶点坐标输入属性（序号0，坐标）对应
	glEnableVertexAttribArray(0);  // 允许Vertex着色器中输入变量0读取显存数据。

	glBindBuffer(GL_ARRAY_BUFFER, vboHandle[1]);//缓冲区数据（纹理）和顶点绑定
	glBufferData(GL_ARRAY_BUFFER, 3 * 2 * elementNum * sizeof(float), textcol, GL_STATIC_DRAW);//内存数据复制到显存
	glVertexAttribPointer((GLuint)1, 2, GL_FLOAT, GL_FALSE, 0, ((GLubyte*)NULL + (0)));//Vertex Shader的顶点颜色输入（序号1，颜色）属性对应
	glEnableVertexAttribArray(1);  //  // 允许Vertex着色器中输入变量1读取显存数据。

	glBindVertexArray(0);


	delete[] vertex;
	delete[] normal;
	delete[] textcol;

}

void cgCube::Render()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glBindVertexArray(vaoHandle);
	glDrawArrays(GL_TRIANGLES, 0, 3 * elementNum);
	glBindVertexArray(0);

	glBindTexture(GL_TEXTURE_2D, 0);
}

void cgCube::Render(mat4 projection)
{
	//Empty
}

void cgCube::SetPosition(vec3 position)
{
	centerPosition = position;
}

vec3 cgCube::GetPosition()
{
	return centerPosition;
}

void cgCube::CalculateModelMatrix()
{
	model = glm::translate(centerPosition);
	auto m = glm::scale(vec3(10, 0.1, 10));
	model = model * m;
}

void cgCube::Update()
{
	// Empty
}

void cgCube::SetTextureID(unsigned int texture_id)
{
	textureID = texture_id;
}

unsigned int cgCube::GetTextureID()
{
	return textureID;
}

void cgCube::polygon(float* vertex, float* textcol, int &vindex, int& tindex, int a, int b, int c, int d, float data[8][3])
{
	//四边形分成2个三角形
	vertex[vindex++] = data[a][0]; vertex[vindex++] = data[a][1]; vertex[vindex++] = data[a][2];//顶点坐标
	textcol[tindex++] = 0; textcol[tindex++] = 0;

	vertex[vindex++] = data[b][0]; vertex[vindex++] = data[b][1]; vertex[vindex++] = data[b][2];	//法向量
	textcol[tindex++] = 1; textcol[tindex++] = 0;

	vertex[vindex++] = data[d][0]; vertex[vindex++] = data[d][1]; vertex[vindex++] = data[d][2];
	textcol[tindex++] = 0; textcol[tindex++] = 1;

	///2
	vertex[vindex++] = data[b][0]; vertex[vindex++] = data[b][1]; vertex[vindex++] = data[b][2];	//法向量
	textcol[tindex++] = 1; textcol[tindex++] = 0;

	vertex[vindex++] = data[c][0]; vertex[vindex++] = data[c][1]; vertex[vindex++] = data[c][2];	//法向量
	textcol[tindex++] = 1; textcol[tindex++] = 1;
	
	vertex[vindex++] = data[d][0]; vertex[vindex++] = data[d][1]; vertex[vindex++] = data[d][2];
	textcol[tindex++] = 0; textcol[tindex++] = 1;
}





