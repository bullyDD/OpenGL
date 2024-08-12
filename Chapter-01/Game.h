/**
* @file: Game.h
* @author  : Y.BINYOUM
* @brief   : Skeleton class that contains code for initialization and shutdown the game.
*            as well as processing user input, run the game loop and generate output.
* @license : BSD
* @version : 0.1
* @date : 08.2024
*
*/
#pragma once
#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "GLAD/glad.h"
#include <iostream>

class Game
{
public:

	// Constructor
	Game();
	~Game();
	
	// Initialize the game
	bool Initialize();
	void Runloop();
	void Shutdown();

private:

	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();

	GLFWwindow* mWindow;
};

