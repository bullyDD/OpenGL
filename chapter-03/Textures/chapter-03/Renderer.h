/**
* @file   : Renderer.h
* @author : Y.BINYOUM
* @brief  : Skeleton class for render engine. It contains code for
*           initialization, run and shutdown the engine. As well as
*	        others methods for engine update, rendering and manage
*           user inputs.
* @license : BSD
* @version : 0.1
* @date    : 08.2024
* 
*/

#ifndef RENDER_H
#define RENDER_H

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

#include <vector>

class Renderer
{
public:

	// Default constructor
	Renderer();

	// Constructor by copy
	Renderer(Renderer&);

	// Destructor
	~Renderer();

	// Initialize the engine
	bool Initialize();

	// Run the engine until user exit
	void Runloop();

	// Shutdown the engine
	void Shutdown();

	void Add(class Scene*);


private:

	void ProcessInput();
	void Update();
	void Render();

	  //------------------//
	 // MEMBER VARIABLES //
	//------------------//

	const int WIDTH = 800;
	const int HEIGHT = 600;
	const char* TITLE = "Learn Opengl - Textures";

	GLFWwindow* mWindow;
	std::vector<class Scene*> mScenes;

	float mixValue;
};

#endif