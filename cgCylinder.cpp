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
	float* textcol = new float[2 * 3 * elementNum];

	float dalpha = 2 * PI / m;
	float dh = (float)height / (float)n;
	float h = -height / 2;
	float texture_radius = 0.5f;

	int vindex = 0;
	int nindex = 0;
	int tindex = 0;
	vec3 vnormal;

	// ����
	for (int i = 0; i < n; i++)
	{
		float alpha = 0.f;	// Բ��
		float z1 = h;
		float z2 = h + dh;

		h += dh;
		// ����
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


			// ����
			float talpha0 = alpha / (2 * PI);
			float talpha1 = (alpha + dalpha) / (2 * PI);

			float tbeta0 = (h + (height / 2)) / height;
			float tbeta1 = (h + dh + (height / 2)) / height;


			// ��һ��������
			vertex[vindex++] = x01; vertex[vindex++] = y01; vertex[vindex++] = z1;
			vnormal = glm::normalize(vec3(x01, y01, z1));
			normal[nindex++] = vnormal.x; normal[nindex++] = vnormal.y; normal[nindex++] = vnormal.z;
			textcol[tindex++] = talpha0; textcol[tindex++] = tbeta0;

			vertex[vindex++] = x02; vertex[vindex++] = y02; vertex[vindex++] = z1;
			vnormal = glm::normalize(vec3(x02, y02, z1));
			normal[nindex++] = vnormal.x; normal[nindex++] = vnormal.y; normal[nindex++] = vnormal.z;
			textcol[tindex++] = talpha1; textcol[tindex++] = tbeta0;

			vertex[vindex++] = x11; vertex[vindex++] = y11; vertex[vindex++] = z2;
			vnormal = glm::normalize(vec3(x11, y11, z2));
			normal[nindex++] = vnormal.x; normal[nindex++] = vnormal.y; normal[nindex++] = vnormal.z;
			textcol[tindex++] = talpha0; textcol[tindex++] = tbeta1;

			// �ڶ���������
			vertex[vindex++] = x02; vertex[vindex++] = y02; vertex[vindex++] = z1;
			vnormal = glm::normalize(vec3(x02, y02, z1));
			normal[nindex++] = vnormal.x; normal[nindex++] = vnormal.y; normal[nindex++] = vnormal.z;
			textcol[tindex++] = talpha1; textcol[tindex++] = tbeta0;

			vertex[vindex++] = x12; vertex[vindex++] = y12; vertex[vindex++] = z2;
			vnormal = glm::normalize(vec3(x12, y12, z2));
			normal[nindex++] = vnormal.x; normal[nindex++] = vnormal.y; normal[nindex++] = vnormal.z;
			textcol[tindex++] = talpha1 ; textcol[tindex++] = tbeta1;

			vertex[vindex++] = x11; vertex[vindex++] = y11; vertex[vindex++] = z2;
			vnormal = glm::normalize(vec3(x11, y11, z2));
			normal[nindex++] = vnormal.x; normal[nindex++] = vnormal.y; normal[nindex++] = vnormal.z;
			textcol[tindex++] = talpha0; textcol[tindex++] = tbeta1;


			alpha += dalpha;
		}
	}
	
	// �϶���
	float alpha = 0.f;
	for (int i = 0; i < m; i++)
	{
		// ����
		float z1 = height / 2;
		
		float x01 = radius * cos(alpha);
		float y01 = radius * sin(alpha);

		float x02 = radius * cos(alpha + dalpha);
		float y02 = radius * sin(alpha + dalpha);

		float x11 = 0;
		float y11 = 0;

		// ����
		float tx01 = texture_radius * cos(alpha) + 0.5f;
		float ty01 = texture_radius * sin(alpha) + 0.5f;

		float tx02 = texture_radius * cos(alpha + dalpha) + 0.5;
		float ty02 = texture_radius * sin(alpha + dalpha) + 0.5;

		float tx11 = 0.5f;
		float ty11 = 0.5f;

		// ��һ��������
		vertex[vindex++] = x01; vertex[vindex++] = y01; vertex[vindex++] = z1;
		vnormal = glm::normalize(vec3(x01, y01, z1));
		normal[nindex++] = vnormal.x; normal[nindex++] = vnormal.y; normal[nindex++] = vnormal.z;
		textcol[tindex++] = tx01; textcol[tindex++] = ty01; 

		vertex[vindex++] = x02; vertex[vindex++] = y02; vertex[vindex++] = z1;
		vnormal = glm::normalize(vec3(x02, y02, z1));
		normal[nindex++] = vnormal.x; normal[nindex++] = vnormal.y; normal[nindex++] = vnormal.z;
		textcol[tindex++] = tx02;	textcol[tindex++] = ty02;

		vertex[vindex++] = x11; vertex[vindex++] = y11; vertex[vindex++] = z1;
		vnormal = glm::normalize(vec3(x11, y11, z1));
		normal[nindex++] = vnormal.x; normal[nindex++] = vnormal.y; normal[nindex++] = vnormal.z;
		textcol[tindex++] = tx11;	textcol[tindex++] = ty11;


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

		// ����
		float tx01 = texture_radius * cos(alpha) + 0.5f;
		float ty01 = texture_radius * sin(alpha) + 0.5f;

		float tx02 = texture_radius * cos(alpha + dalpha) + 0.5;
		float ty02 = texture_radius * sin(alpha + dalpha) + 0.5;

		float tx11 = 0.5f;
		float ty11 = 0.5f;

		// ��һ��������
		vertex[vindex++] = x01; vertex[vindex++] = y01; vertex[vindex++] = z1;
		vnormal = glm::normalize(vec3(x01, y01, z1));
		normal[nindex++] = vnormal.x; normal[nindex++] = vnormal.y; normal[nindex++] = vnormal.z;
		textcol[tindex++] = tx01; textcol[tindex++] = ty01;

		vertex[vindex++] = x02; vertex[vindex++] = y02; vertex[vindex++] = z1;
		vnormal = glm::normalize(vec3(x02, y02, z1));
		normal[nindex++] = vnormal.x; normal[nindex++] = vnormal.y; normal[nindex++] = vnormal.z;
		textcol[tindex++] = tx02;	textcol[tindex++] = ty02;

		vertex[vindex++] = x11; vertex[vindex++] = y11; vertex[vindex++] = z1;
		vnormal = glm::normalize(vec3(x11, y11, z1));
		normal[nindex++] = vnormal.x; normal[nindex++] = vnormal.y; normal[nindex++] = vnormal.z;
		textcol[tindex++] = tx11;	textcol[tindex++] = ty11;

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
	glBufferData(GL_ARRAY_BUFFER, 3 * 2 * elementNum * sizeof(float), textcol, GL_STATIC_DRAW);//�ڴ����ݸ��Ƶ��Դ�
	glVertexAttribPointer((GLuint)1, 2, GL_FLOAT, GL_FALSE, 0, ((GLubyte*)NULL + (0)));//Vertex Shader�Ķ�����ɫ���루���1����ɫ�����Զ�Ӧ
	glEnableVertexAttribArray(1);  //  // ����Vertex��ɫ�����������1��ȡ�Դ����ݡ�

	glBindBuffer(GL_ARRAY_BUFFER, vboHandle[2]);//���������ݣ���ɫ���Ͷ����
	glBufferData(GL_ARRAY_BUFFER, 3 * 3 * elementNum * sizeof(float), normal, GL_STATIC_DRAW);//�ڴ����ݸ��Ƶ��Դ�
	glVertexAttribPointer((GLuint)2, 3, GL_FLOAT, GL_FALSE, 0, ((GLubyte*)NULL + (0)));//Vertex Shader�Ķ�����ɫ���루���1����ɫ�����Զ�Ӧ
	glEnableVertexAttribArray(2);  //  // ����Vertex��ɫ�����������1��ȡ�Դ����ݡ�

	glBindVertexArray(0);

	delete[] vertex;
	delete[] normal;
	delete[] textcol;
}

void cgCylinder::Render()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glBindVertexArray(vaoHandle);
	glDrawArrays(GL_TRIANGLES, 0, 3 * elementNum);
	glBindVertexArray(0);

	glBindTexture(GL_TEXTURE_2D, 0);
}

void cgCylinder::Render(mat4 projection)
{
	// Empty
}

void cgCylinder::SetPosition(vec3 position)
{
	centerPosition = position;
}

void cgCylinder::SetRotateInfo(std::vector<float> angle, std::vector<vec3> roller)
{
	rotateInfo = std::tuple<std::vector<float>, std::vector<vec3>>(angle, roller);
}

vec3 cgCylinder::GetPosition()
{
	return centerPosition;
}

void cgCylinder::CalcuteModelMatrix()
{
	model = glm::translate(centerPosition);

	for (int i = 0; i < std::get<0>(rotateInfo).size(); i++)
	{
		float angle = glm::radians(std::get<0>(rotateInfo)[i]);
		vec3 roller = std::get<1>(rotateInfo)[i];
		model = model * glm::rotate(angle, roller);
	}
}

void cgCylinder::Update()
{
	//Empty
}

void cgCylinder::SetTextureID(unsigned int texture_id)
{
	textureID = texture_id;
}

unsigned int cgCylinder::GetTextureID()
{
	return textureID;
}
