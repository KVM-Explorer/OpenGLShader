#version 430

in float value;

out vec4 FragColor;

uniform float maxValue;
uniform float minValue;

uniform vec4 minColor;
uniform vec4 maxColor;

vec3 hsv2rgb(vec3 c)
{
    vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
    vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
    return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
}

void main()
{
    vec4 color= mix( minColor,maxColor,smoothstep(minValue, maxValue, value)); 
    
    vec3 hsvtorgb = hsv2rgb(vec3(color.xyz));

    FragColor = vec4(hsvtorgb,1);
}