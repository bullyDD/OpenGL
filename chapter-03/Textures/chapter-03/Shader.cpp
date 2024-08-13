#include "Shader.h"

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	// 1. file for storing vertex, fragment shader source code
	std::string vertexCode, fragmentCode;

	std::ifstream vShaderFile, fShaderFile;

	// 2. Ensure exception are raise
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		// 3. Open file
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);

		// 4. Convert buffer'content into stream
		std::stringstream vShaderStream, fShaderStream;

		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		// 5. Make sure to close file
		vShaderFile.close();
		fShaderFile.close();

		// 6. Convert stream into string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();

	}
	catch (std::exception e)
	{
		std::cout << "ERROR::FAILED_READING_FILE" << std::endl;
	}
}

Shader::~Shader()
{
	std::cout << "SHADER::DESTRUCTOR::CALL" << std::endl;
}

void Shader::Use()
{
	glUseProgram(ID);
}

void Shader::SetInt(std::string& name, int value) const
{
}

void Shader::SetBool(std::string& name, bool value) const
{
}

void Shader::SetFloat(std::string& name, float value) const
{
}
