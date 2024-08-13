#include "Shader.h"


  //--------------------------//
 //    GLOBALES VARIABLES    //
//--------------------------//

const int BUFFER_SIZE = 512;

  //--------------------------------------//
 //    SERVICES FUNCTIONS PROTOTYPES     //
//--------------------------------------//

void CheckForErrors(unsigned int, const char*);


Shader::Shader()
{
}

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{

	// 1. Retrieve the vertex, fragment source code from filepath
	std::string vertexCode;
	std::string fragmentCode;

	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	// 2. Ensure ifstream objects can throw exceptions
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		// 3. Open files
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);

		// 4. Read file'buffer contents into stream
		std::stringstream vShaderStream, fShaderStream;

		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		// Close file handlers
		vShaderFile.close();
		fShaderFile.close();

		// Convert stream into string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();

	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ : " << std::endl;
	}
	
	// Now we convert string into const char* bc opengl needs it
	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();

	// Now we create vertex, fragment shader programs, compile them and check for errors
	//----------------------------------------------------------------------------------

	int success;
	char infoLog[512];

	// Vertex shader
	unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	CheckForErrors(vertex, "VERTEX");


	// fragment shader
	unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	CheckForErrors(fragment, "FRAGMENT");


	// Shader program
	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	CheckForErrors(ID, "PROGRAM");

	// Delete unused shaders
	glDeleteShader(vertex);
	glDeleteShader(fragment);
	
}

Shader::~Shader()
{
	std::cout << "SHADER::DESTRUCTOR::CALL"<< std::endl;
	//glDeleteProgram(ID);
}

void Shader::Use()
{
	glUseProgram(ID);
}

void Shader::SetInt(const std::string& name, int value) const
{
	int location = glGetUniformLocation(ID, name.c_str());
	glUniform1i(location, value);
}

void Shader::SetBool(const std::string& name, bool value) const
{
	int location = glGetUniformLocation(ID, name.c_str());
	glUniform1i(location, int(value));
}

void Shader::SetFloat(const std::string& name, float value) const
{
	int location = glGetUniformLocation(ID, name.c_str());
	glUniform1f(location, value);
}


  //-----------------------------------------//
 //      SERVICES FUNCTIONS DEFINITION      //
//-----------------------------------------//

/// <summary>
/// Check for compilation or linking errors depending on @shader's @type 
/// </summary>
/// <param name="shader"></param>
/// <param name="type"></param>
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
			std::cout << "ERROR::SHADER::" << type <<  ": " << infoLog;
		}
	}
	else
	{
		glLinkProgram(shader);

		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shader, BUFFER_SIZE, NULL, infoLog);
			std::cout << "ERROR::SHADER::" << type << ": " << infoLog;
		}
	}
	
}