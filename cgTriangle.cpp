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

	// 定义顶点
	
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
	
	

	glGenVertexArrays(1, &vaoHandle);//生成顶点数组，与 vertex shader 绑定
	glBindVertexArray(vaoHandle);//可以多个顶点数组，使用时需要激活哪一个

	glBindBuffer(GL_ARRAY_BUFFER, vboHandle[0]);//激活（绑定）当前缓冲区
	glBufferData(GL_ARRAY_BUFFER, 3 * 2 * sizeof(float), vertc, GL_STATIC_DRAW);//内存数据复制到显存
	
	glVertexAttribPointer((GLuint)0, 2, GL_FLOAT, GL_FALSE, 0, ((GLubyte*)NULL +(0)));//Vertex Shader 的顶点坐标输入属性（序号 0，坐标）对应
	glEnableVertexAttribArray(0); // 允许 Vertex 着色器中输入变量 0 读取显存数据。
	glBindBuffer(GL_ARRAY_BUFFER, vboHandle[1]);//缓冲区数据（颜色）和顶点绑定
	glBufferData(GL_ARRAY_BUFFER, 3 * 3 * sizeof(float), color, GL_STATIC_DRAW);//内存数据复制到显存

	glVertexAttribPointer((GLuint)1, 3, GL_FLOAT, GL_FALSE, 0, ((GLubyte*)NULL +(0)));//Vertex Shader 的顶点颜色输入（序号 1，颜色）属性对应
	glEnableVertexAttribArray(1); // // 允许 Vertex 着色器中输入变量 1 读取显存数据。
	glBindVertexArray(0);

}

void cgTriangle::Render(mat4 projection)
{
	//启用需要的 shader，可以动态切换不同的 shader
	prog.Use();
	prog.SetUniform("ProjectionMatrix", projection);
	prog.SetUniform("ModelMatrix", model);
	glBindVertexArray(vaoHandle);
	glDrawArrays(GL_TRIANGLES, 0, 3);//GL_LINES 线段
	glBindVertexArray(0);
	////关闭所用的 shader
	prog.Unuse();
}

void cgTriangle::CalculateModelMatrix()
{
	//计算矩阵，先执行的矩阵后计算

	model = glm::translate(vec3(300.0f, 400.0f, 0.0f));
	model *= glm::rotate(alpha,vec3( 0.0f, 0.0f, 1.0f));
	model *= glm::scale(vec3(0.4f, 0.4f, 1.0f));
	model *= glm::translate(vec3(-300.0f, -400.0f, -0.0f));

}
