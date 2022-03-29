#version 430

layout (location = 0) in vec3  VertexPosition;
layout (location = 1) in float VertexValue;

out float value;

uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;

void main()
{
    vec3 FragPos = vec3(ModelMatrix * vec4(VertexPosition, 1.0));
    value = VertexValue;

    gl_Position = ProjectionMatrix * ViewMatrix * vec4(FragPos, 1.0);
}