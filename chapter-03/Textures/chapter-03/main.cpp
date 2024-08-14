/**
* @file : main.cpp
* @author : Y.BINYOUM
* @brief  : Program that initialize, run and shutdown the renderer.
* @license : BSD
* @version : 0.1
* @date : 08.2024
* 
*/
#include "Renderer.h"

int main(int argc, char* argv[])
{
	Renderer renderer2D;
	bool success = renderer2D.Initialize();

	if (success)
	{
		renderer2D.Runloop();
	}

	renderer2D.Shutdown();

	return 0;
}