/**
* @file: Renderer.h
* @author: Y.BINYOUM
* @brief: skeleton class for 2D renderer engine based on openGL. It contains
* code for Initialization, run and shutdown the renderer. As well as
* code for process user input, update the renderer and finally generate
* some outputs.
* 
*/


#pragma once

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "GLAD/glad.h"

class Renderer
{
public:	
	// Default constructor
	Renderer();

	// Constructor by copy
	Renderer(Renderer&);

	// Destructor
	~Renderer();

	// Initialize the renderer
	bool Initialize();
	void Runloop();
	void Shutdown();

private:

	void ProcessInput();
	void Update();
	void GenerateOutput();

	// Members variables

	// Pointer to glfw window object
	GLFWwindow* mWindow;

};

