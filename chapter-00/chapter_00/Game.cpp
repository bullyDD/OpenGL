#include "Game.h"
#include <iostream>


//****** GLOBAL VARIABLES *******//

const int WIDTH = 800;
const int HEIGHT = 600;
const char* TITLE = "Learn OpenGL - Chapter 00";

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
" gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 fragColor;\n"
"void main()\n"
"{\n"
" fragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);\n"
"}\0";

// vertices array is a collection of 3 vectices. Each vertex having a 3D
// position

float vertices[] = {
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f
};

// OpenGL buffer objects : VAO, VBO
//---------------------------------

unsigned int VAO, VBO;
unsigned int shaderProgram;

//**** SERVICES FUNCTION PROTYPES ******//
void framebuffer_size_CB(GLFWwindow*, int, int);

Game::Game() : 
	mWindow(nullptr)
{
}

Game::~Game()
{
	std::cout << "DESTRUCTOR::Call\n";
}

bool Game::Initialize()
{
	/** INITIALIZE GLFW **/
	if (!glfwInit()) 
	{
		std::cout << "ERROR::GLFW::Initialization failed\n";
		return false;
	}

	// Set glfw window hint
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// Create glfw window objet and store its memory address in
	// game prperty mWindow

	mWindow = glfwCreateWindow(WIDTH, HEIGHT, TITLE, NULL, NULL);
	if (mWindow == nullptr)
	{
		std::cout << "ERROR::GLFW::Initialization failed\n";
		return false;
	}

	glfwMakeContextCurrent(mWindow);
	glfwSetFramebufferSizeCallback(mWindow, framebuffer_size_CB);

	//glad : Load all openGL functer pointers
	//------------------------------------------

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "ERROR::GLAD::Failed to initialize glad\n";
		return false;
	}

	int success;
	char infoLog[512];

	//VERTEX SHADER : Load vertex shader from source, compile it and check for errors
	//--------------------------------------------------------------------------------

	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);

	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX:" << infoLog << std::endl;
	}

	//FRAGMENT SHADER : Load vertex shader from source, compile it and check for errors
	//--------------------------------------------------------------------------------

	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT:" << infoLog << std::endl;
	}

	// SHADER PROGRAM : Attach vertex and fragment shaders then check for linking errors
	// When linking the shaders into a program, it links the output of each shader to the
	// input of the next shader.
	//--------------------------------------------------------------------------------
	shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM:" << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


	// OpenGL buffer objects : Generate buffer, objects, bind and configure them. 
	//---------------------------------------------------------------------------

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

		// 0. copy our vertices array in a buffer for OpenGL to use
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		// 1. then set the vertex attributes pointers
		// Vertex attribute configurations
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(0));
		glEnableVertexAttribArray(0);

		// note that this is allowed, the call to glVertexAttribPointer registered VBO as 
		// the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
		glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Unbind Vertex Array Object
	glBindVertexArray(0);

	
	return true;
}

void Game::Runloop()
{
	while (!glfwWindowShouldClose(mWindow))
	{
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}

void Game::Shutdown()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);

	//glfwDestroyWindow(mWindow);	 no need bc glfwTerminate() does the job.

	glfwTerminate();		// GLFW: terminate, clearing all previously allocated GLFW resources
	std::cout << "SHUTDOWN::CALL\n";
}

void Game::ProcessInput()
{
	if (glfwGetKey(mWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(mWindow, true);
	}
}

void Game::UpdateGame()
{
}

void Game::GenerateOutput()
{
	// Clear color buffer with a green dark color
	glClearColor(0.21f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	// Rendering
	//------------
	
	// If we want to draw wireframe polygones

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glUseProgram(shaderProgram);
	glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);

	// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
	// -------------------------------------------------------------------------------
	glfwSwapBuffers(mWindow);
	glfwPollEvents();
}


//******* SERVICE FUNCTION DEFINITION ********/

void framebuffer_size_CB(GLFWwindow*, int width, int height)
{
	glViewport(0, 0, width, height);
}