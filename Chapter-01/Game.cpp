#include "Game.h"

// Globals variables :
//---------------------

const int WIDTH = 800;
const int HEIGHT = 600;
const char* TITLE = "Chapter 01 : Rectangle";

// Shaders source code
//--------------------

const char *vertexShaderSource = "#version 330 core\n"
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

//OpenGL objects
//------------------

unsigned int VAO{ 0 };
unsigned int VBO{ 0 };
unsigned int EBO{ 0 };

unsigned int shaderProgram{ 0 };

// Vertices data
//---------------

float vertices[] = {
	 0.5f,  0.5f, 0.0f,	// Top Right
	 0.5f, -0.5f, 0.0f,	// Bottom Right
	-0.5f, -0.5f, 0.0f,	// Bottom Left
	-0.5f,  0.5f, 0.0f	// Top Left
};

// OpenGL needs to know indices order to draw our two triangles
unsigned int indices[] = {
	0, 1, 3,
	1, 2, 3
};


// SERVICES FUNCTIONS
//----------------------

void framebuffer_Size_CB(GLFWwindow*, int, int);


Game::Game() : mWindow(nullptr)
{
}

Game::~Game()
{
	std::cout << "DESTRUCTOR::CALL::End game class" << std::endl;
}

bool Game::Initialize()
{
	//GLFW : Initialize and set window hints
	//---------------------------------------

	if (!glfwInit())
	{
		std::cout << "ERROR::GLFW::Initialization failed" << std::endl;
		return false;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// GLFW window : create a temporary glfw window object and save its memory address
	// to a member variable mWindow
	//--------------------------------------------------------------------------
	mWindow = glfwCreateWindow(WIDTH, HEIGHT, TITLE, NULL, NULL);
	if (mWindow == nullptr)
	{
		std::cout << "ERROR:GLFW::Failed to create window" << std::endl;
		return false;
	}

	glfwMakeContextCurrent(mWindow);
	glfwSetFramebufferSizeCallback(mWindow, framebuffer_Size_CB);

	// GLAD : Load all openGL pointers functions
	//-------------------------------------------

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "ERROR::GLAD::Failed loading" << std::endl;
		return false;
	}

	// OpenGL Buffer Objects : Generate, bind and load data to GPU
	//--------------------------------------------------------------

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	std::cout << "VAO= " <<  VAO << std::endl;
	std::cout << "VBO = " << VBO << std::endl;
	std::cout << "EBO = " << EBO << std::endl;

	// Bind VAO
	glBindVertexArray(VAO);

		// Load and copy data to the GPU
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		// Set Attributes pointers
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Unbind VAO
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// Shaders :  Create shaders (vertex , fragment) load source code, compile
	//            check for errors and then link them to send data through each 
	//            stage of Graphic pipeline.
	//---------------------------------------------------------------------------

	int success;
	char infoLog[512];

	// Vertex shader
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX:" << infoLog << std::endl;
	}
	

	// fragment shader
	unsigned int fragementShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragementShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragementShader);

	glGetShaderiv(fragementShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragementShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT:" << infoLog << std::endl;
	}

	// Shader program
	shaderProgram = glCreateProgram();
	std::cout << "shader = " << shaderProgram << std::endl;

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragementShader);

	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM:" << infoLog << std::endl;
	}

	// Delete unused shaders
	glDeleteShader(vertexShader);
	glDeleteShader(fragementShader);

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
	glDeleteBuffers(1, &EBO);

	glfwTerminate();		// Free unused memory. 
}

void Game::ProcessInput()
{
	if (glfwGetKey(mWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(mWindow, GL_TRUE);
	}
}

void Game::UpdateGame()
{
}

void Game::GenerateOutput()
{
	// Clear back buffer with dark green color
	
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);


	// Rendering
	//-----------
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glUseProgram(shaderProgram);
	glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	// GLFW : swap buffer and poll events such as user keyboard, audio, and so on
	//---------------------------------------------------------------------------

	glfwSwapBuffers(mWindow);
	glfwPollEvents();
}


void framebuffer_Size_CB(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

