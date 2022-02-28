#include "pch.h"
#include "cgTriangle.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/constants.hpp>


cgTriangle::cgTriangle()
{
	alpha = 30;
}

cgTriangle::~cgTriangle()
{
}

void cgTriangle::Init()
{
	// Comiplier Shader
	prog.CompileShader("Shader/basic.vs");
	prog.CompileShader("Shader/basic.fs");
	prog.Link();

	// ���嶥��
	
	float vertc[3 * 2];	
	float color[3 * 3];

	int countv = 0;
	int countc = 0;

	vertc[countv++] = 100.f, vertc[countv++] = 100.f;
	color[countc++] = 1.f, color[countc++] = 0.f, color[countc++] = 0.f;

	vertc[countv++] = 500.f, vertc[countv++] = 100.f;
	color[countc++] = 0.f, color[countc++] = 1.f, color[countc++] = 0.f;

	vertc[countv++] = 300.f, vertc[countv++] = 400.f;
	color[countc++] = 0.f, color[countc++] = 0.f, color[countc++] = 1.f;

	glGenBuffers(2, vboHandle);
	
	

	glGenVertexArrays(1, &vaoHandle);//���ɶ������飬�� vertex shader ��
	glBindVertexArray(vaoHandle);//���Զ���������飬ʹ��ʱ��Ҫ������һ��

	glBindBuffer(GL_ARRAY_BUFFER, vboHandle[0]);//����󶨣���ǰ������
	glBufferData(GL_ARRAY_BUFFER, 3 * 2 * sizeof(float), vertc, GL_STATIC_DRAW);//�ڴ����ݸ��Ƶ��Դ�
	
	glVertexAttribPointer((GLuint)0, 2, GL_FLOAT, GL_FALSE, 0, ((GLubyte*)NULL +(0)));//Vertex Shader �Ķ��������������ԣ���� 0�����꣩��Ӧ
	glEnableVertexAttribArray(0); // ���� Vertex ��ɫ����������� 0 ��ȡ�Դ����ݡ�
	glBindBuffer(GL_ARRAY_BUFFER, vboHandle[1]);//���������ݣ���ɫ���Ͷ����
	glBufferData(GL_ARRAY_BUFFER, 3 * 3 * sizeof(float), color, GL_STATIC_DRAW);//�ڴ����ݸ��Ƶ��Դ�

	glVertexAttribPointer((GLuint)1, 3, GL_FLOAT, GL_FALSE, 0, ((GLubyte*)NULL +(0)));//Vertex Shader �Ķ�����ɫ���루��� 1����ɫ�����Զ�Ӧ
	glEnableVertexAttribArray(1); // // ���� Vertex ��ɫ����������� 1 ��ȡ�Դ����ݡ�
	glBindVertexArray(0);

}

void cgTriangle::Render(mat4 projection)
{
	//������Ҫ�� shader�����Զ�̬�л���ͬ�� shader
	prog.Use();
	prog.SetUniform("ProjectionMatrix", projection);
	prog.SetUniform("ModelMatrix", model);
	glBindVertexArray(vaoHandle);
	glDrawArrays(GL_TRIANGLES, 0, 3);//GL_LINES �߶�
	glBindVertexArray(0);
	////�ر����õ� shader
	prog.Unuse();
}

void cgTriangle::CalculateModelMatrix()
{
	//���������ִ�еľ�������

	model = glm::translate(vec3(300.0f, 400.0f, 0.0f));
	model *= glm::rotate(alpha,vec3( 0.0f, 0.0f, 1.0f));
	model *= glm::scale(vec3(0.4f, 0.4f, 1.0f));
	model *= glm::translate(vec3(-300.0f, -400.0f, -0.0f));

}
