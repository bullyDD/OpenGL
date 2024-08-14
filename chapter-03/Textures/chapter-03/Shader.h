#ifndef SHADER_H
#define SHADER_H

#include "GLAD/glad.h"

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

class Shader
{
public:

	// Shader program Unique identifier
	unsigned int ID;

	// Default constructor
	Shader();

	// Constructor with 2 arguments
	Shader(const char* vertexPath, const char* fragmentPath);

	// Destructor
	~Shader();

	// Activate/Use the program
	void Use();

	// Uniform utilities
	void SetInt(std::string& name, int value) const;
	void SetBool(std::string& name, bool value) const;
	void SetFloat(std::string& name, float value) const;

};

#endif
