/**
* @file: Main.cpp
* @author: Y.BINYOUM
* @brief: Program that intialize and run the render engine until it is 
*		shutdown by user.
* @license : BSD
* @version : 0.1
* @date : 0.1
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