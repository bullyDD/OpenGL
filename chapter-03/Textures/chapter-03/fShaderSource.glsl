#version 330 core

out vec4 FragColor;
in vec3 ourColor;
in vec2 ourTexCoord;

uniform sampler2D containerTex;
uniform sampler2D faceTex;
uniform float mixValue;

void main()
{
	FragColor = mix(texture(containerTex, ourTexCoord), texture(faceTex, ourTexCoord), mixValue); //* vec4(ourColor, 1.0f);
}