#include "pch.h"
#include "cgCube.h"
#include <math.h>
#include <GL/glew.h>//OpenGL��
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

	float* vertex = new float[3 * 3 * elementNum];
	float* normal = new float[3 * 3 * elementNum];

	// ����
	polygon(vertex,vindex,7,6,2,3, origin);
	for (int i = 0; i < 6; i++)
	{
		normal[nindex++] = 0; normal[nindex++] = 1; normal[nindex++] = 0;
	}

	// ����
	polygon(vertex, vindex, 4, 5, 1, 0, origin);
	for (int i = 0; i < 6; i++)
	{
		normal[nindex++] = 0; normal[nindex++] = -1; normal[nindex++] = 0;
	}

	// ǰ��
	polygon(vertex, vindex, 4,5,6,7, origin);
	for (int i = 0; i < 6; i++)
	{
		normal[nindex++] = 0; normal[nindex++] = 0; normal[nindex++] = 1;
	}

	// ����
	polygon(vertex, vindex,0,1,2,3 , origin);
	for (int i = 0; i < 6; i++)
	{
		normal[nindex++] = 0; normal[nindex++] = 0; normal[nindex++] = -1;
	}

	// ����
	polygon(vertex, vindex, 0,3,7,4, origin);
	for (int i = 0; i < 6; i++)
	{
		normal[nindex++] = -1; normal[nindex++] = 0; normal[nindex++] = 0;
	}
	// ����
	polygon(vertex, vindex, 1,2,6,5, origin);
	for (int i = 0; i < 6; i++)
	{
		normal[nindex++] = 1; normal[nindex++] = 0; normal[nindex++] = 0;
	}

	glGenBuffers(2, vboHandle);//���ɻ�����������

	glGenVertexArrays(1, &vaoHandle);//���ɶ������飬��vertex shader��
	glBindVertexArray(vaoHandle);//���Զ���������飬ʹ��ʱ��Ҫ������һ��

	glBindBuffer(GL_ARRAY_BUFFER, vboHandle[0]);//����󶨣���ǰ������
	glBufferData(GL_ARRAY_BUFFER, 3 * 3 * elementNum * sizeof(float), vertex, GL_STATIC_DRAW);//�ڴ����ݸ��Ƶ��Դ�
	glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, ((GLubyte*)NULL + (0)));//Vertex Shader�Ķ��������������ԣ����0�����꣩��Ӧ
	glEnableVertexAttribArray(0);  // ����Vertex��ɫ�����������0��ȡ�Դ����ݡ�

	//glBindBuffer(GL_ARRAY_BUFFER, vboHandle[1]);//���������ݣ������Ͷ����
	//glBufferData(GL_ARRAY_BUFFER, 3 * 2 * elementNum * sizeof(float), textcor, GL_STATIC_DRAW);//�ڴ����ݸ��Ƶ��Դ�
	//glVertexAttribPointer((GLuint)1, 2, GL_FLOAT, GL_FALSE, 0, ((GLubyte*)NULL + (0)));//Vertex Shader�Ķ�����ɫ���루���1����ɫ�����Զ�Ӧ
	//glEnableVertexAttribArray(1);  //  // ����Vertex��ɫ�����������1��ȡ�Դ����ݡ�

	glBindVertexArray(0);


	delete[] vertex;
	delete[] normal;

}

void cgCube::Render()
{
	glBindVertexArray(vaoHandle);
	glDrawArrays(GL_TRIANGLES, 0, 3 * elementNum);
	glBindVertexArray(0);
}

void cgCube::Render(mat4 projection)
{
	//Todo Achieve this
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

void cgCube::polygon(float* vertex, int &vindex, int a, int b, int c, int d, float data[8][3])
{
	//�ı��ηֳ�2��������
	vertex[vindex++] = data[a][0]; vertex[vindex++] = data[a][1]; vertex[vindex++] = data[a][2];//��������

	vertex[vindex++] = data[b][0]; vertex[vindex++] = data[b][1]; vertex[vindex++] = data[b][2];	//������

	vertex[vindex++] = data[d][0]; vertex[vindex++] = data[d][1]; vertex[vindex++] = data[d][2];
	///2
	vertex[vindex++] = data[b][0]; vertex[vindex++] = data[b][1]; vertex[vindex++] = data[b][2];	//������

	vertex[vindex++] = data[c][0]; vertex[vindex++] = data[c][1]; vertex[vindex++] = data[c][2];	//������

	vertex[vindex++] = data[d][0]; vertex[vindex++] = data[d][1]; vertex[vindex++] = data[d][2];

}





