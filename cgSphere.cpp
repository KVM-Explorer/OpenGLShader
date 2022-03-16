#include "pch.h"
#include "cgSphere.h"
#include <math.h>
#include <GL/glew.h>//OpenGL��
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/constants.hpp>

cgSphere::cgSphere()
{
	radius = 1.f;
	centerPosition = vec3(0.f, 0.f, -10.f);
	elementNum = 0;
	textureID = -1;
}

cgSphere::cgSphere(float r)
{
	radius = r;
	centerPosition = vec3(0.f, 0.f, -10.f);
	elementNum = 0;
}

cgSphere::~cgSphere()
{
	
}

void cgSphere::Init()
{
	int m = 20;	// ��ֱ��Ƭ
	int n = 20;	// ˮƽ��Ƭ
	elementNum = m * n * 2;
	
	float* vertex = new float[3 * 3 * elementNum];
	float* normal = new float[3 * 3 * elementNum];
	

	float dalpha = 2 * PI / m;
	float dbeta = PI / n;
	float beta = -PI / 2.f;

	int vindex = 0;
	int nindex = 0;
	vec3 vnormal;

	for (int i = 0; i < n; i++)
	{
		float alpha = 0.f;

		float z1 = radius * sin(beta);
		float z2 = radius * sin(beta + dbeta);

		float r1 = radius * cos(beta);
		float r2 = radius * cos(beta + dbeta);

		beta += dbeta;
		for (int j = 0; j < m; j++)
		{
			float x01 = r1 * cos(alpha);
			float y01 = r1 * sin(alpha);

			float x02 = r1 * cos(alpha + dalpha);
			float y02 = r1 * sin(alpha + dalpha);

			float x11 = r2 * cos(alpha);
			float y11 = r2 * sin(alpha);

			float x12 = r2 * cos(alpha + dalpha);
			float y12 = r2 * sin(alpha + dalpha);

			/*
				 11 12
				 01 02
			*/
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

void cgSphere::Render()
{
	if (textureID == -1)
	{
		glBindVertexArray(vaoHandle);
		glDrawArrays(GL_TRIANGLES, 0, 3 * elementNum);
		glBindVertexArray(0);
	}
	else
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureID);

		glBindVertexArray(vaoHandle);
		glDrawArrays(GL_TRIANGLES, 0, 3 * elementNum);
		glBindVertexArray(0);

		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

void cgSphere::Render(mat4 projection)
{
	//Empty
}

void cgSphere::SetPosition(vec3 position)
{
	centerPosition = position;
}

vec3 cgSphere::GetPosition()
{
	return centerPosition;
}

void cgSphere::CalculateModelMatrix()
{
	model = glm::translate(centerPosition);
}

void cgSphere::Update()
{
	// Empty
}

void cgSphere::SetTextureID(unsigned int texture_id)
{
	textureID = texture_id;
}
