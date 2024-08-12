/**
* @file: vertex_shader.glsl
* @author : Y.BINYOUM
* @brief  : Code for the first stage of rendering 
*          graphic pipeline.
* 
*/
#version 330 core

layout (location = 0) in vec3 aPos;

void main()
{
	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}