#version 430

layout (location = 0) in vec3  VertexPosition;
layout (location = 1) in float VertexValue;

out vec3 Color;

uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;

uniform float maxValue;
uniform float minValue;

uniform vec4 minColor;
uniform vec4 maxColor;

uniform int blockNum;


vec3 hsv2rgb(vec3 c)
{
    vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
    vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
    return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
}
float value2level(float min_val,float max_val,float value)
{
    float ans = 0.f;
    if(value>max_val) return 1.f;
    if(value<min_val) return 0.f;
    int step = int(max_val-min_val)/blockNum;
    return (int(value-min_val)/step)/10.f;
}
void main()
{
    vec4  color= mix(minColor,maxColor,value2level(minValue,maxValue,VertexValue));  
    Color = hsv2rgb(vec3(color.xyz));
    gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix* vec4(VertexPosition, 1.0);
}