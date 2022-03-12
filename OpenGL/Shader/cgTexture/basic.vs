#version 430 //版本号
//输入
layout (location = 0) in vec3 VertexPosition; //顶点坐标
layout (location = 1) in vec2 VertexTextureCoord;
//输出
out vec2 TextureCoord; //顶点颜色
//uniform
uniform mat4 ProjectionMatrix;
uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
void main()
{
    TextureCoord = VertexTextureCoord;
    gl_Position = ProjectionMatrix *ViewMatrix* ModelMatrix*vec4(VertexPosition,1.0);
}
