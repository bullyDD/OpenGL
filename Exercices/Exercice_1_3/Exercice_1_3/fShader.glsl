#version 330 core

in vec2 ourTexCoord;
out vec4 FragColor;

uniform sampler2D containerTex;
uniform sampler2D faceTex;
uniform float mixValue;

void main()
{
	FragColor = mix(texture(faceTex, ourTexCoord), texture(containerTex, ourTexCoord), mixValue);
}