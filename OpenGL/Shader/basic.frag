#version 430
in vec3 Color;
out vec4 FragColor;
void main() 
{
 FragColor = vec4(Color, 1.0);// 改成这个 vec4(1,0,0, 1.0)试试
}