#pragma once
#include "pch.h"
#include "RayTrace.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/constants.hpp>


RayTrace::RayTrace()
{
	alpha = 30;
	centerPosition = vec3(0.f, 0.f, -10.f);
	elementNum = 0;
}

RayTrace::~RayTrace()
{
}

void RayTrace::Init()
{
	elementNum = 1;
	// Comiplier Shader
	prog.CompileShader("Shader/computer/raytrace.vert");
	prog.CompileShader("Shader/computer/raytrace.frag");
	prog.Link();

	// ���嶥��

	float vertc[4 * 2];
	float color[4 * 3];

	int countv = 0;
	//int countc = 0;

	vertc[countv++] = -1.f, vertc[countv++] = -1.f;
	vertc[countv++] = -1.f, vertc[countv++] = 1.f;
	vertc[countv++] = 1.f, vertc[countv++] = -1.f;
	vertc[countv++] = 1.f, vertc[countv++] = 1.f;

	glGenBuffers(2, vboHandle);

	glGenVertexArrays(1, &vaoHandle);//���ɶ������飬�� vertex shader ��
	glBindVertexArray(vaoHandle);//���Զ���������飬ʹ��ʱ��Ҫ������һ��

	glBindBuffer(GL_ARRAY_BUFFER, vboHandle[0]);//����󶨣���ǰ������
	glBufferData(GL_ARRAY_BUFFER, 4 * 2 * sizeof(float), vertc, GL_STATIC_DRAW);//�ڴ����ݸ��Ƶ��Դ�

	glVertexAttribPointer((GLuint)0, 2, GL_FLOAT, GL_FALSE, 0, ((GLubyte*)NULL + (0)));//Vertex Shader �Ķ��������������ԣ���� 0�����꣩��Ӧ
	glEnableVertexAttribArray(0); // ���� Vertex ��ɫ����������� 0 ��ȡ�Դ����ݡ�

	glBindVertexArray(0);

}

void RayTrace::Render(mat4 projection)
{
	//������Ҫ�� shader�����Զ�̬�л���ͬ�� shader
	prog.Use();

	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(vaoHandle);
	glBindTexture(GL_TEXTURE_2D,textureID);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);//GL_LINES �߶�
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);

	//�ر����õ� shader
	prog.Unuse();
}

void RayTrace::CalculateModelMatrix()
{
	//���������ִ�еľ�������

	//model = glm::translate(vec3(300.0f, 400.0f, 0.0f));
	//model *= glm::rotate(alpha, vec3(0.0f, 0.0f, 1.0f));
	//model *= glm::scale(vec3(0.4f, 0.4f, 1.0f));
	//model *= glm::translate(vec3(-300.0f, -400.0f, -0.0f));

}

void RayTrace::Render()
{
	glBindVertexArray(vaoHandle);
	glDrawArrays(GL_TRIANGLE_STRIP, 0,  2*4);
	glBindVertexArray(0);
}

void RayTrace::SetPosition(vec3 position)
{
	centerPosition = position;
}

vec3 RayTrace::GetPosition()
{
	return centerPosition;
}
