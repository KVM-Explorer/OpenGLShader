
#include "pch.h"
#include "cgRectangle.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/constants.hpp>

cgRectangle::cgRectangle(float angle, vec3 trans)
{
    alpha = angle;
    translateVector = trans;
    colorType = 0;
}

cgRectangle::~cgRectangle()
{
}

void cgRectangle::Init()
{ 
    // Comiplier Shader
    prog.CompileShader("Shader/cgRectangle/basic.vs");
    prog.CompileShader("Shader/cgRectangle/basic.frag");
    prog.Link();

    // ���嶥��
    float vertc[12];  GenerateVertex(vertc);
    float color[12];  GenerateColor(color,colorType);

    glGenBuffers(2, vboHandle);

    glGenVertexArrays(1, &vaoHandle); //���ɶ������飬�� vertex shader ��
    glBindVertexArray(vaoHandle);     //���Զ���������飬ʹ��ʱ��Ҫ������һ��

    glBindBuffer(GL_ARRAY_BUFFER, vboHandle[0]);                                        //����󶨣���ǰ������
    glBufferData(GL_ARRAY_BUFFER, pointNum * 3 * sizeof(float), vertc, GL_STATIC_DRAW); //�ڴ����ݸ��Ƶ��Դ�
    glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, ((GLubyte *)NULL + (0))); // Vertex Shader �Ķ��������������ԣ���� 0�����꣩��Ӧ
    glEnableVertexAttribArray(0);   // ���� Vertex ��ɫ����������� 0 ��ȡ�Դ����ݡ�
   
    glBindBuffer(GL_ARRAY_BUFFER, vboHandle[1]);                                         //���������ݣ���ɫ���Ͷ����
    glBufferData(GL_ARRAY_BUFFER, pointNum * 3 * sizeof(float), color, GL_STATIC_DRAW);  //�ڴ����ݸ��Ƶ��Դ�
    glVertexAttribPointer((GLuint)1, 3, GL_FLOAT, GL_FALSE, 0, ((GLubyte *)NULL + (0))); // Vertex Shader �Ķ�����ɫ���루��� 1����ɫ�����Զ�Ӧ
    glEnableVertexAttribArray(1);                                                        // // ���� Vertex ��ɫ����������� 1 ��ȡ�Դ����ݡ�
    glBindVertexArray(0);

}

void cgRectangle::Render()
{
}

void cgRectangle::Render(mat4 projection)
{
    //������Ҫ�� shader�����Զ�̬�л���ͬ�� shader
    prog.Use();
    prog.SetUniform("ProjectionMatrix", projection);
    prog.SetUniform("ModelMatrix", model);
    glBindVertexArray(vaoHandle);
    
    glDrawArrays(GL_LINE_LOOP, 0, pointNum); // GL_LINES �߶�
    glBindVertexArray(0);
    
    prog.Unuse();
}

void cgRectangle::CalculateModelMatrix()
{
    //���������ִ�еľ�������
    model = glm::translate(translateVector);
    model *= glm::rotate(alpha, vec3(0.0f, 0.0f, 1.0f));
}

void cgRectangle::GenerateVertex(float *vectex)
{
    float center_x = 0;
    float center_y = 0;
    int min_radius = 300;
    int num = 0 ;
    for (int i = 0; i < 4; i++)
    {
        float angle = -45 +i* 90;
        // x y z
        vectex[num]     = center_x + min_radius*cos(angle*3.14f/180.f);
        vectex[num+1]   = center_y + min_radius*sin(angle*3.14f/180.f);
        vectex[num+2] = 0;
        num+=3;
    }
}

void cgRectangle::GenerateColor(float *color, int type)
{
    int num = 0 ;
    for (int i = 0; i < 4; i++)
    {
        color[num] = 0.25f;
        color[num+1] = 0.5f;
        color[num+2] = 1.0f;
        num+=3;
    }
}

void cgRectangle::SetPosition(int angle, vec3 position)
{
}
