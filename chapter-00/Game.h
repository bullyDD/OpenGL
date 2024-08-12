/**
* @file   : Game.h
* @author : Y.BINYOUM
* @brief  : Game class skeleton. It contains code that initialize
*          and shutdown the game. As well as code for running, 
*          processInput, update and generate output while the
*          game is running.
* @license : BSD
* @version : 0.1
* @date    : 08.2024
*/
#pragma once

#define GLFW_INCLUDE_NONE
#include "GLFW\glfw3.h"
#include "glad\glad.h"

// ** MATH OBJECT **//
struct Vector3D {
	float x, y, z;
};

class Game
{
public:
	Game();
	~Game();

	bool Initialize();
	void Runloop();
	void Shutdown();

private:

	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();

	// Pointer to glfw window objetc
	GLFWwindow* mWindow;
};

