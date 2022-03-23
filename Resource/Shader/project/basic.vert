#version 430 //版本号
//输入
layout (location = 0) in vec3 VertexPosition; //顶点坐标
layout (location = 1) in vec3 VertexColor; //顶点颜色
//输出
out vec3 Color; //顶点颜色
//uniform
uniform mat4 ProjectionMatrix;
uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
void main()
{
    Color = VertexColor;
    gl_Position = ProjectionMatrix * ViewMatrix *ModelMatrix*vec4(VertexPosition,1.0);
}
