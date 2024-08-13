/**
* @file: Shader.h
* @author : Y.BINYOUM
* @brief  : The shader class holds the ID of the shader program. Its constructor requires the file paths of
*           the source code of the vertex and fragment shader respectively that we can store on disk as simple
*           text files.
* @license : BSD
* @version : 0.1
* @date    : 08.2024
* 
*/

#pragma once

#include "GLAD/glad.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:

	// the shader program
	unsigned int ID;

	// Default constructor
	Shader();

	// The constructor reads and built the shader
	Shader(const char* vertexPath, const char* fragmentPath);
	~Shader();


	// Use and activate the shader program
	void Use();

	// Utility uniform functions
	void SetInt(const std::string& name, int value) const;
	void SetBool(const std::string& name, bool value) const;
	void SetFloat(const std::string& name, float value) const;

};
