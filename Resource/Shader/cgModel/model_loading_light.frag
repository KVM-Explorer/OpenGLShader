#version 430 core
out vec4 FragColor;
in vec3 Normal;
in vec3 Position;
in vec2 TexCoords;

uniform sampler2D texture_diffuse1;

uniform int shiness;//高光系数
uniform vec3 lightColor;
uniform vec3 ambientColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

void main()
{    
    vec3 ambient = ambientColor * vec3(texture(texture_diffuse1,TexCoords));

    vec3 norm = normalize(Normal);
    vec3 lightDirection = normalize(lightPos-Position);
    float diff = max(dot(norm,lightDirection),0.0);
    vec3 diffuse = lightColor*diff*vec3(texture(texture_diffuse1,TexCoords));

    vec3 viewDirection = normalize(viewPos- Position);
    vec3 reflectDirection = reflect(-lightDirection,norm);
    float spec = pow(max(dot(viewDirection,reflectDirection),0.0),shiness);
    vec3 specular = lightColor*spec*vec3(texture(texture_diffuse1,TexCoords));
    vec3 Color = ambient+diffuse+specular;


    FragColor = vec4(Color,1.0);
}