#include "Shader.h"

  //--------------------//
 // GLOBALES VARIABLES //
//--------------------//


const int BUFFER_SIZE = 1024;

  //--------------------------------//
 // SERVICES FUNCTIONS PROTOTYPES  //
//--------------------------------//

void CheckForErrors(unsigned int, const char*);

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

	// convert string into const char*
	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();

	// Vertex
	unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	CheckForErrors(vertex, "VERTEX");

	// Fragment
	unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(vertex, 1, &fShaderCode, NULL);
	CheckForErrors(vertex, "FRAGMENT");

	// Program
	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	CheckForErrors(ID, "PROGRAM");

	// Once the shader program has link each shader, we can delete them
	glDeleteShader(vertex);
	glDeleteShader(fragment);
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
	int location = glGetUniformLocation(ID, name.c_str());
	glUniform1i(location, value);
}

void Shader::SetBool(std::string& name, bool value) const
{
	int location = glGetUniformLocation(ID, name.c_str());
	glUniform1i(location, (int)value);
}

void Shader::SetFloat(std::string& name, float value) const
{
	int location = glGetUniformLocation(ID, name.c_str());
	glUniform1f(location, value);
}

  //--------------------------------//
 // SERVICES FUNCTIONS DEFINITIONS //
//--------------------------------//

void CheckForErrors(unsigned int shader, const char* type)
{
	int success;
	char infoLog[BUFFER_SIZE];

	if (type != "PROGRAM")
	{
		glCompileShader(shader);
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

		if (!success)
		{
			glGetShaderInfoLog(shader, BUFFER_SIZE, NULL, infoLog);
			std::cout << "ERROR::SHADER::" << type << ":" << infoLog << std::endl;
		}
	}
	else
	{
		glLinkProgram(shader);
		glGetProgramiv(shader, GL_LINK_STATUS, &success);

		if (!success)
		{
			glGetProgramInfoLog(shader, BUFFER_SIZE, NULL, infoLog);
			std::cout << "ERROR::SHADER::" << type << ":" << infoLog << std::endl;
		}

	}
}
