#version 430 //版本号
//输入
layout (location = 0) in vec2 VertexPosition; //顶点坐标
layout (location = 1) in vec3 VertexColor; //顶点颜色
//输出
out vec3 Color; //顶点颜色
//uniform
uniform mat4 ProjectionMatrix;
uniform mat4 ModelMatrix;
void main()
{
 Color = VertexColor;
 vec3 vertex_position = vec3(VertexPosition.x,VertexPosition.y,0);
 gl_Position = ProjectionMatrix * ModelMatrix*vec4(vertex_position,1.0);
 //gl_Position = ProjectionMatrix * ModelMatrix*vec4(VertexPosition,1.0);
}
