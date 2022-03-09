#version 430 //版本号
//输入
layout (location = 0) in vec3 VertexPosition;
//layout (location = 1) in vec3 VertexColor;
//输出
out vec3 Color;
//uniform 变量
uniform mat4 ProjectionMatrix;
uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform vec3 ObjectColor;

void main()
{
 Color = ObjectColor;
 mat4 mvp=ProjectionMatrix * ViewMatrix * ModelMatrix;
 gl_Position = mvp * vec4(VertexPosition,1.0);
}