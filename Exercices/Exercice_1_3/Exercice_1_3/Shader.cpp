#include "Shader.h"

//=============== SERVICES FUNCTIONS PROTOTYPES ================//

void CheckForCompileErrors(unsigned int, const char*);

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	// Store shader inside character buffer
	std::string vertexCode, fragmentCode;
	std::ifstream vShaderFile, fShaderFile;

	// Ensure exceptions are raised
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);

		// Convert buffer' content into stream
		std::stringstream vShaderStream, fShaderStream;

		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		// Close files
		vShaderFile.close();
		fShaderFile.close();

		// Convert stream into string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();

	}
	catch (std::exception e)
	{
		std::cout << "ERROR::Failed to open file" << std::endl;
	}

	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	// Vertex
	unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vertexSource, NULL);
	CheckForCompileErrors(vertex, "VERTEX");

	// fragment
	unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fragmentSource, NULL);
	CheckForCompileErrors(fragment, "FRAGMENT");

	//shader
	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	CheckForCompileErrors(ID, "PROGRAM");

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void Shader::Use()
{
	glUseProgram(ID);
}

void Shader::SetInt(const char* name, int value) const
{
	glUniform1i(glGetUniformLocation(ID, name), value);
}

void Shader::SetBool(const char* name, bool value) const
{
	glUniform1i(glGetUniformLocation(ID, name), (int)value);
}

void Shader::SetFloat(const char* name, float value) const
{
	glUniform1f(glGetUniformLocation(ID, name), value);
}

void Shader::SetMat4(const char* name, glm::mat4 mat) const
{
	glUniformMatrix4fv(glGetUniformLocation(ID, name), 1, GL_FALSE, glm::value_ptr(mat));
}

//========== SERVICES FUNCTIONS DEFINITIONS ==============//

void CheckForCompileErrors(unsigned int shader, const char* type)
{
	int success;
	char infoLog[1024];

	if (type != "PROGRAM")
	{
		glCompileShader(shader);
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::SHADER:: " << type << ":" << infoLog << std::endl;
		}
	}
	else
	{
		glLinkProgram(shader);
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::SHADER:: " << type << ":" << infoLog << std::endl;
		}
	}

}