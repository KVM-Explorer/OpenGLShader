#version 460 core

out vec4 FragColor;

uniform sampler2D ComTexture;

void main()
{
    // FragColor = vec4(1.f,0.f,0.f,1.f);
	FragColor = texture(ComTexture, vec2(gl_FragCoord.xy) / vec2(textureSize(ComTexture, 0)));
}
