/**
* @file: main.cpp
* @author : Y.BINYOUM
* @brief : Main program initialize, run and shutdown the engine when
*			user press either esc key or cross icon on the current window.
* @license : BSD
* @version : 0.1
* @date    : 08.2024
* 
*/

#include "Engine.h"

int main(int argc, char *argv[])
{
	Engine engine;
	bool success = engine.Initialize();

	if (success)
	{
		engine.Runloop();
	}

	engine.Shutdown();
	return 0;
}