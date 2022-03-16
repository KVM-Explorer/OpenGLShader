#version 430 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;


//输出
out vec3 Normal;
out vec3 Position;
out vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    Position = vec3(model* vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(model))) * aNormal;//计算模型变换后的法向
    TexCoords = aTexCoords;    
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}