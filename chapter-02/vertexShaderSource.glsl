#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

uniform float dx;
out vec4 ourColor;

void main()
{
	gl_Position = vec4(aPos.x + dx, -aPos.y, aPos.z, 1.0f);
	ourColor    = vec4(aColor, 1.0f);
}