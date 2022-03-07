#include "pch.h"
#include "cgPentagram.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/constants.hpp>

cgPentagram::cgPentagram(float angle = 0,vec3 trans = vec3(0,0,0))
{
    alpha  = angle;
    translateVector = trans;
	colorType = 0;
}

cgPentagram::~cgPentagram()
{

}

void cgPentagram::Init()
{
    // Comiplier Shader
	prog.CompileShader("Shader/cgPentagram/basic.vs");
	prog.CompileShader("Shader/cgPentagram/basic.frag");
	prog.Link();

	// ���嶥��
	float vertc[30];	GenerateVertex(vertc);
	float color[30];	GenerateColor(color);


	glGenBuffers(2, vboHandle);
	
	

	glGenVertexArrays(1, &vaoHandle);//���ɶ������飬�� vertex shader ��
	glBindVertexArray(vaoHandle);//���Զ���������飬ʹ��ʱ��Ҫ������һ��

	glBindBuffer(GL_ARRAY_BUFFER, vboHandle[0]);//����󶨣���ǰ������
	glBufferData(GL_ARRAY_BUFFER, pointNum * 3 * sizeof(float), vertc, GL_STATIC_DRAW);//�ڴ����ݸ��Ƶ��Դ�
	
	glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, ((GLubyte*)NULL +(0)));//Vertex Shader �Ķ��������������ԣ���� 0�����꣩��Ӧ
	glEnableVertexAttribArray(0); // ���� Vertex ��ɫ����������� 0 ��ȡ�Դ����ݡ�
	glBindBuffer(GL_ARRAY_BUFFER, vboHandle[1]);//���������ݣ���ɫ���Ͷ����
	glBufferData(GL_ARRAY_BUFFER, pointNum * 3 * sizeof(float), color, GL_STATIC_DRAW);//�ڴ����ݸ��Ƶ��Դ�

	glVertexAttribPointer((GLuint)1, 3, GL_FLOAT, GL_FALSE, 0, ((GLubyte*)NULL +(0)));//Vertex Shader �Ķ�����ɫ���루��� 1����ɫ�����Զ�Ӧ
	glEnableVertexAttribArray(1); // // ���� Vertex ��ɫ����������� 1 ��ȡ�Դ����ݡ�
	glBindVertexArray(0);
}

void cgPentagram::Render(mat4 projection)
{
    //������Ҫ�� shader�����Զ�̬�л���ͬ�� shader
	prog.Use();
	prog.SetUniform("ProjectionMatrix", projection);
	prog.SetUniform("ModelMatrix", model);
	glBindVertexArray(vaoHandle);
	switch (colorType)
	{
	case 0:
		glDrawArrays(GL_LINE_LOOP, 0, pointNum);//GL_LINES �߶�
		break;
	case 1:
	case 2:
		glDrawArrays(GL_POLYGON, 0, pointNum);
		break;
	default:
		break;
	}
	
	glBindVertexArray(0);
	prog.Unuse();
}

void cgPentagram::SetType(int type)
{
	colorType = type;
}

void cgPentagram::CalculateModelMatrix()
{
	//���������ִ�еľ�������
	model = glm::translate(translateVector);
	model *= glm::rotate(alpha,vec3( 0.0f, 0.0f, 1.0f));
}

void cgPentagram::GenerateVertex(float* vertex)
{
	int center_x = 0;
	int center_y = 0;

	float min_radius = 60;
	float max_radius = 120;

	int num = 0;

	for (int i = 18; i < 378; i += 72)
	{
		int dx = center_x + cos((i - 36.f) * 3.14f / 180.f) * min_radius;
		int dy = center_y + sin((i - 36.f) * 3.14f / 180.f) * min_radius;
		vertex[num] = dx, vertex[num + 1] = dy, vertex[num + 2] = 0;
		dx = center_x + cos(i * 3.14 / 180.f) * max_radius;
		dy = center_y + sin(i * 3.14 / 180.f) * max_radius;
		vertex[num + 3] = dx, vertex[num + 4] = dy, vertex[num + 5] = 0;
		num += 6;
	}
}

void cgPentagram::GenerateColor(float* color)
{
	int num = 0;
	for (int i = 0; i < 360; i += 72)
	{
		switch (colorType)
		{
			case 0:
				color[num] = 1, color[num + 1] =1, color[num + 2] = 1;
				color[num + 3] = 1, color[num + 4] = 1, color[num + 5] = 1;
				break;
			case 1:
				color[num] = 0, color[num + 1] = 1, color[num + 2] = 1;
				color[num + 3] = 0, color[num + 4] = 1, color[num + 5] = 1;
				break;
			case 2:
				color[num] = 0, color[num + 1] = 0.6, color[num + 2] = 0.5;
				color[num + 3] = 1, color[num + 4] = 0.38, color[num + 5] =0;
				break;
		}
		
		num += 6;
	}
}

int cgPentagram::GetPosition()
{
	return alpha;
}

void cgPentagram::SetPosition(int angle,vec3 position)
{
	alpha = angle;
	//if (alpha > 360) alpha -= 360;
	translateVector = position;
}
