#include "Renderer.h"
#include "Scene.h"
#include "GLAD/glad.h"

#include <iostream>

   //--------------------------------------//
  //   SERVICES FUNCTIONS PROTOTYPES      //
 //--------------------------------------//

void frameBufferSize_Cb(GLFWwindow*, int, int);


Renderer::Renderer() : mWindow(nullptr), mixValue(0.0f)
{
}

Renderer::Renderer(Renderer& r)
{
	r.mWindow = mWindow;
	r.mScenes = mScenes;
}

Renderer::~Renderer()
{
	std::cout << "RENDERER::DESTRUCTOR::CALL" << std::endl;
	while (!mScenes.empty())
	{
		// Object not delete : Memory waste
		mScenes.pop_back();
	}
}

bool Renderer::Initialize()
{
	 // GLFW : Initialization and set window hint
	//-------------------------------------------
	if (!glfwInit())
	{
		std::cout << "ERROR::GLFW::INITIALIZATION_FAILED" << std::endl;
		return false;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	 //GLFW Window: create a window object and check for errors
	//----------------------------------------------------------

	mWindow = glfwCreateWindow(WIDTH, HEIGHT, TITLE, NULL, NULL);
	if (mWindow == nullptr)
	{
		std::cout << "ERROR::GLFW::FAILED_CREATE_WINDOW" << std::endl;
		return false;
	}

	glfwMakeContextCurrent(mWindow);
	glfwSetFramebufferSizeCallback(mWindow, frameBufferSize_Cb);


	 // GLAD : Load OpenGL functions pointer
	//--------------------------------------

	if (!gladLoadGLLoader(GLADloadproc(glfwGetProcAddress)))
	{
		std::cout << "ERROR::GLAD::FAILED_LOADING_FUNCTIONS" << std::endl;
		return false;
	}

	// First scene
	Scene firstScene(this);
	bool success = firstScene.Initialize();

	if (!success)
	{
		std::cout << "ERROR::SCENE::INITIALIZATION_FAILED" << std::endl;
	}

	return true;
}

void Renderer::Runloop()
{
	while (!glfwWindowShouldClose(mWindow))
	{
		float dt = static_cast<float>(glfwGetTime());
		ProcessInput();
		Update();
		Render();
	}
}

void Renderer::Shutdown()
{
	glfwDestroyWindow(mWindow);
	glfwTerminate();
}

void Renderer::Add(Scene* s)
{
	mScenes.emplace_back(s);
}

void Renderer::ProcessInput()
{
	if (glfwGetKey(mWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(mWindow, GL_TRUE);
	}
	// TODO mixValue
	if (glfwGetKey(mWindow, GLFW_KEY_UP) == GLFW_PRESS)
	{
		mixValue += 0.1;
	}
}

void Renderer::Update()
{
	std::cout << "Dt from Renderer = " << mixValue << std::endl;
	for (auto scene : mScenes)
	{
		scene->Update(mixValue);
	}
}

void Renderer::Render()
{
	// Clear color buffer with light grey color
	glClearColor(0.6f, 0.6f, 0.6f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);


	// Render stufff
	for (auto scene : mScenes)
	{
		if (scene->GetSceneState() == Scene::EState::EACTIVE)
		{
			scene->Draw();
		}
		else
		{
			std::cout << "ERROR::SCENE:UNAVAILABLE" << std::endl;
		}
	}

	// glfw swap and poll events
	//--------------------------

	glfwSwapBuffers(mWindow);
	glfwPollEvents();

}


  //--------------------------------------//
 //   SERVICES FUNCTIONS DEFINITIONS      //
//--------------------------------------//

void frameBufferSize_Cb(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}