#include "Renderer.h"
#include "Shader.h"

#include <iostream>

  //------------------------//
 //  GLOBALES VARIABLES    //
//------------------------//

const int WIDTH = 800;
const int HEIGHT = 600;
const char* TITLE = "Learn OpenGL - Shaders ";
const int BUFFER_SIZE = 1024;

// Vertices data

float vertices[] = {
	// Position						// Color
	 0.5f, -0.5f, 0.0f,				1.0f, 0.0f, 0.0f,
	-0.5f, -0.5f, 0.0f,			    0.0f, 1.0f, 0.0f,
	 0.0f,  0.5f, 0.0f,				0.0f, 0.0f, 1.0f
};	


// OpenGL buffer objects
//-------------------- 

unsigned int VAO, VBO, shader;
float step;

  //---------------------------------//
 // SERVICES FUNCTIONS PROTOTYPES   //
//---------------------------------//

void frameBufferSizeCb(GLFWwindow*, int, int);

Renderer::Renderer() : mWindow(nullptr), mShader(nullptr)
{
}


Renderer::Renderer(Renderer& r) 
{
	this->mWindow = r.mWindow;
	this->mShader = r.mShader;
}

Renderer::~Renderer()
{
	std::cout << "RENDERER::DESTRUCTOR::CALL" << std::endl;
}

bool Renderer::Initialize()
{
	// GLFW : Initialization and set up for window hints
	//--------------------------------------------------

	if (!glfwInit())
	{
		std::cout << "ERROR::GLFW:Failed to initialize" << std::endl;
		return false;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// Window
	mWindow = glfwCreateWindow(WIDTH, HEIGHT, TITLE, NULL, NULL);
	if (mWindow == nullptr)
	{
		std::cout << "ERROR::GLFW:Failed to create glfw window" << std::endl;
		return false;
	}

	glfwMakeContextCurrent(mWindow);
	glfwSetFramebufferSizeCallback(mWindow, frameBufferSizeCb);

	// GLAD : Load opengl pointer functions
	//--------------------------------------

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "ERROR::GLAD:Failed to load opengl functions" << std::endl;
		return false;
	}

	// Build and compile our shader
	//------------------------------

	//shaders program
	//----------------
	const char* vertex   = "vertexShaderSource.glsl";
	const char* fragment = "fragmentShaderSource.glsl";

	Shader ourShader(vertex, fragment);
	mShader = &ourShader;
	mShader->Use();

	std::cout << "shader = " << mShader->ID << std::endl;

	// Buffer objects
	//---------------

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		// Enable attribute pointer for position
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		// Enable attribute pointer for color
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	return true;
}

void Renderer::Runloop()
{
	while (!glfwWindowShouldClose(mWindow))
	{
		ProcessInput();
		Update();
		GenerateOutput();
	}
}

void Renderer::Shutdown()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(mShader->ID);

	glfwDestroyWindow(mWindow);
	glfwTerminate();
}

void Renderer::ProcessInput()
{
	// Stop the render engine when user press escape key
	if (glfwGetKey(mWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(mWindow, GL_TRUE);
	}
}

void Renderer::Update()
{
	step = sin(glfwGetTime() / 2.0f);
}

void Renderer::GenerateOutput()
{
	// Clear buffer color with light gray
	glClearColor(0.6f, 0.6f, 0.6f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	// Render stuff
	//-------------
	
	mShader->Use();
	mShader->SetFloat("dx", step);

	glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);
	
	//GLFW Swap buffers (front and back) and poll events such as user input, audio

	glfwSwapBuffers(mWindow);
	glfwPollEvents();

}

  //---------------------------------//
 //  SERVICES FUNCTIONS DEFINITIONS //
//---------------------------------//

void frameBufferSizeCb(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}