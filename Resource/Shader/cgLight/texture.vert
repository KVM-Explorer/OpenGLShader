#version 430 //版本号
//输入
layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec2 VertexTexture;
layout (location = 2) in vec3 VertexNormal;


//输出
out vec3 Normal;
out vec3 Position;
out vec2 TexCoords;
//uniform 变量
uniform mat4 ProjectionMatrix;
uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
void main()
{
 Position = vec3(ModelMatrix* vec4(VertexPosition, 1.0));
 Normal = mat3(transpose(inverse(ModelMatrix))) * VertexNormal;//计算模型变换后的法向
 TexCoords = VertexTexture;
 mat4 mvp=ProjectionMatrix * ViewMatrix * ModelMatrix;
 gl_Position = mvp * vec4(VertexPosition,1.0);
}