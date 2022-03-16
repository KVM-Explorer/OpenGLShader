#version 430

in vec2 TextureCoord;
out vec4 FragColor;

layout(binding=0) uniform sampler2D texture0;
void main() 
{
    vec4 text_color = texture(texture0,TextureCoord);
    FragColor = text_color;
}