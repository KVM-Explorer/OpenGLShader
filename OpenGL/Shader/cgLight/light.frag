#version 430

in vec3 Color;

out vec4 FragColor;
uniform vec3 objectColor;

void main() 
{
    FragColor = vec4(Color*objectColor, 1.0);
}
