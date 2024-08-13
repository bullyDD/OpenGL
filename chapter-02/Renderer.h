/**
* @file : Renderer.h
* @author : Y.BINYOUM
* @brief : Skeleton for render engine. It contains code for 
* Initialization, loop execution and shutdown the engine. As
* well as code for processing user input, generate output and update
* the engine.
* @license : BSD
* @version : 0.1
* @date : 08.2024
*/
#pragma once

#define GLFW_INCLUDE_NONE

#include "GLFW/glfw3.h"
#include "GLAD/glad.h"

class Renderer
{
public:

	// default constructor
	Renderer();

	// Constructor by copy
	Renderer(Renderer&);

	// Destructor
	~Renderer();

	// Initialize the engine
	bool Initialize();

	// Run the engine until user press ESC key
	void Runloop();

	// Shutdown the engine
	void Shutdown();

private:

	void ProcessInput();
	void Update();
	void GenerateOutput();

	// Members variables
	GLFWwindow* mWindow;
	class Shader* mShader;
};

