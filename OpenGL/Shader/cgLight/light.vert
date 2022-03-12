#version 430

layout(location=0)in vec3 VertexPosition;
layout(location=1)in vec3 VertexNormal;

out vec3 Color;

uniform mat4 ProjectionMatrix;
uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;

struct LightInfo
{
    vec4 Position;
    vec3 La;    // 环境光
    vec3 Ld;    // 漫反射
    vec3 Ls;    // 镜面反射
};

uniform LightInfo Light;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

uniform vec3 Kd; // Diffuse reflectivity

void main()
{
    // gouraud shading
    vec3 Position = vec3(ModelMatrix* vec4(VertexPosition, 1.0));
    vec3 Normal = mat3(transpose(inverse(ModelMatrix))) * VertexNormal;

    // ambient
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;
  	
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - Position);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    
    // specular
    float specularStrength = 1.0; 
    vec3 viewDir = normalize(viewPos - Position);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;      

    Color = ambient + diffuse + specular;
    // gouraud shading end

    mat4 mvp=ProjectionMatrix * ViewMatrix * ModelMatrix;
    gl_Position = mvp * vec4(VertexPosition,1.0);
}