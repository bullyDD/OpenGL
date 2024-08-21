#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 texCoord;

out vec2 ourTexCoord;
uniform mat4 transform;

void main()
{
	gl_Position = transform * vec4(aPos.x, aPos.y, aPos.z, 1.0f);
	ourTexCoord = texCoord;
}