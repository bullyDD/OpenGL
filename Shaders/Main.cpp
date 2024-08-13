/**
* @file : Main.cpp
* @author : Y.BINYOUM
* @brief : Program that initialize, run and shutdown the render engine.
* @license : BSD
* @version : 0.1
* @date : 08.2024
* 
*/

#include "Renderer.h"

int main()
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