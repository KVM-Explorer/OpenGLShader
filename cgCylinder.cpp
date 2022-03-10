#include "pch.h"
#include "cgCylinder.h"
#include <math.h>
#include <GL/glew.h>//OpenGL��
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
	int m = 20;	// Բ��Ƭ
	int n = 20;	// �߷�Ƭ
	elementNum = m * n * 2 + 2 * m;

	float* vertex = new float[3 * 3 * elementNum];
	float* normal = new float[3 * 3 * elementNum];

	float dalpha = 2 * PI / m;
	float dh = (float)height / (float)n;
	float h = -height / 2;

	int vindex = 0;
	int nindex = 0;
	vec3 vnormal;

	// ����
	for (int i = 0; i < n; i++)
	{
		float alpha = 0.f;	// Բ��
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
			// ��һ��������
			vertex[vindex++] = x01; vertex[vindex++] = y01; vertex[vindex++] = z1;
			vnormal = glm::normalize(vec3(x01, y01, z1));
			normal[nindex++] = vnormal.x; normal[nindex++] = vnormal.y; normal[nindex++] = vnormal.z;

			vertex[vindex++] = x02; vertex[vindex++] = y02; vertex[vindex++] = z1;
			vnormal = glm::normalize(vec3(x02, y02, z1));
			normal[nindex++] = vnormal.x; normal[nindex++] = vnormal.y; normal[nindex++] = vnormal.z;

			vertex[vindex++] = x11; vertex[vindex++] = y11; vertex[vindex++] = z2;
			vnormal = glm::normalize(vec3(x11, y11, z2));
			normal[nindex++] = vnormal.x; normal[nindex++] = vnormal.y; normal[nindex++] = vnormal.z;

			// �ڶ���������
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
	
	// �϶���
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

		// ��һ��������
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

	// �¶���
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

		// ��һ��������
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

	glGenBuffers(3, vboHandle);//���ɻ�����������

	glGenVertexArrays(1, &vaoHandle);//���ɶ������飬��vertex shader��
	glBindVertexArray(vaoHandle);//���Զ���������飬ʹ��ʱ��Ҫ������һ��

	glBindBuffer(GL_ARRAY_BUFFER, vboHandle[0]);//����󶨣���ǰ������
	glBufferData(GL_ARRAY_BUFFER, 3 * 3 * elementNum * sizeof(float), vertex, GL_STATIC_DRAW);//�ڴ����ݸ��Ƶ��Դ�
	glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, ((GLubyte*)NULL + (0)));//Vertex Shader�Ķ��������������ԣ����0�����꣩��Ӧ
	glEnableVertexAttribArray(0);  // ����Vertex��ɫ�����������0��ȡ�Դ����ݡ�

	glBindBuffer(GL_ARRAY_BUFFER, vboHandle[1]);//���������ݣ���ɫ���Ͷ����
	glBufferData(GL_ARRAY_BUFFER, 3 * 3 * elementNum * sizeof(float), normal, GL_STATIC_DRAW);//�ڴ����ݸ��Ƶ��Դ�
	glVertexAttribPointer((GLuint)1, 3, GL_FLOAT, GL_FALSE, 0, ((GLubyte*)NULL + (0)));//Vertex Shader�Ķ�����ɫ���루���1����ɫ�����Զ�Ӧ
	glEnableVertexAttribArray(1);  //  // ����Vertex��ɫ�����������1��ȡ�Դ����ݡ�

	//glBindBuffer(GL_ARRAY_BUFFER, vboHandle[2]);//���������ݣ���ɫ���Ͷ����
	//glBufferData(GL_ARRAY_BUFFER, 3 * 2 * iCount * sizeof(float), textcor, GL_STATIC_DRAW);//�ڴ����ݸ��Ƶ��Դ�
	//glVertexAttribPointer((GLuint)2, 2, GL_FLOAT, GL_FALSE, 0, ((GLubyte*)NULL + (0)));//Vertex Shader�Ķ�����ɫ���루���1����ɫ�����Զ�Ӧ
	//glEnableVertexAttribArray(1);  //  // ����Vertex��ɫ�����������1��ȡ�Դ����ݡ�

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
