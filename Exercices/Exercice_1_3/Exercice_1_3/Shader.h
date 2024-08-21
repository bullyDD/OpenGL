#ifndef SHADEE_H
#define SHADER_H

#include "GLAD/glad.h"
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class Shader
{
public:
	unsigned int ID;

	Shader(const char* vertexPath, const char* fragmentPath);
	void Use();

	 // Uniform utilities
	//--------------------

	void SetInt(const char* name, int value) const;
	void SetBool(const char* name, bool value) const;
	void SetFloat(const char* name, float value) const;
	void SetMat4(const char* name, glm::mat4 mat) const;
};

#endif
